#include "discord.h"

#include <QCoreApplication>
#include <QFile>

Q_LOGGING_CATEGORY(radioDiscord, "radio.discord")

Discord::Discord()
{
    QObject::connect(m_socket,
                     &QLocalSocket::readyRead,
                     this,
                     &Discord::processDataFromSocket);
    QObject::connect(m_socket,
                     &QLocalSocket::stateChanged,
                     this,
                     [this](QLocalSocket::LocalSocketState state)
                     {
                         qCInfo(radioDiscord) << "new socket state:" << state;

                         switch (state)
                         {
                             case QLocalSocket::UnconnectedState:
                             {
                                 m_handshakeState = HANDSHAKE_INACTIVE;

                                 m_reconnectTimer->start();

                                 break;
                             }

                             case QLocalSocket::ConnectedState:
                             {
                                 m_reconnectTimer->stop();

                                 handshake();

                                 break;
                             }
                             default:
                             {
                                 break;
                             }
                         }
                     });
    QObject::connect(m_socket,
                     &QLocalSocket::errorOccurred,
                     this,
                     [this](QLocalSocket::LocalSocketError socketError)
                     {
                         qCCritical(radioDiscord)
                             << "socket error:" << m_socket->errorString()
                             << '(' << socketError << ')';
                     });

    QObject::connect(m_reconnectTimer,
                     &QTimer::timeout,
                     this,
                     [this]
                     {
                         if (m_socket->state()
                             != QLocalSocket::UnconnectedState)
                         {
                             return;
                         }

                         connect();
                     });

    m_reconnectTimer->setInterval(5000);
}

Discord *Discord::instance()
{
    static Discord *instance = new Discord;

    return instance;
}

bool Discord::pipeExists(const int &pipe)
{
    return QFile::exists(
        QString("\\\\.\\pipe\\discord-ipc-%0").arg(QString::number(pipe)));
}

void Discord::connect()
{
    if (m_socket->state() != QLocalSocket::UnconnectedState)
    {
        return;
    }

    if (!pipeExists(m_pipe))
    {
        m_pipe = -1;

        for (int i = 0; i < 10; ++i)
        {
            if (pipeExists(i))
            {
                m_pipe = i;

                break;
            }
        }

        if (m_pipe == -1)
        {
            return;
        }

        qCInfo(radioDiscord) << "using pipe" << m_pipe;
    }

    m_socket->connectToServer(
        QString("discord-ipc-%0").arg(QString::number(m_pipe)));
}

void Discord::handshake()
{
    if (m_handshakeState != HANDSHAKE_INACTIVE)
    {
        return;
    }

    qCInfo(radioDiscord) << "shaking hands with discord";

    m_handshakeState = HANDSHAKE_ACTIVE;

    sendMessage(
        {
            {"client_id", "1401486054418022410"},
            {        "v",                     1}
    },
        HANDSHAKE);
}

void Discord::sendMessage(QJsonObject message,
                          const OperationCode &operationCode)
{
    if (!m_socket->isOpen())
    {
        connect();

        return;
    }

    message["nonce"] = QUuid::createUuid().toString(QUuid::WithoutBraces);

    const QByteArray payload
        = QJsonDocument(message).toJson(QJsonDocument::Compact);
    const MessageHeader messageHeader
        = MessageHeader {operationCode, static_cast<quint32>(payload.size())};

    switch (m_socket->write(
        QByteArray::fromRawData(reinterpret_cast<const char *>(&messageHeader),
                                sizeof(MessageHeader))
        + payload))
    {
        case 0:
        {
            qCCritical(radioDiscord)
                << "message" << message << "was not sent, 0 bytes written";

            break;
        }

        case -1:
        {
            qCCritical(radioDiscord)
                << "message" << message
                << "was not sent:" << m_socket->errorString();

            break;
        }

        default:
        {
            break;
        }
    }
}

void Discord::processDataFromSocket()
{
    while (m_socket->bytesAvailable() > sizeof(MessageHeader))
    {
        const QByteArray rawMessageHeader
            = m_socket->read(sizeof(MessageHeader));
        const MessageHeader messageHeader
            = *reinterpret_cast<const MessageHeader *>(rawMessageHeader.data());

        QJsonParseError messageParseError;
        const QJsonDocument message
            = QJsonDocument::fromJson(m_socket->read(messageHeader.payloadSize),
                                      &messageParseError);

        if (messageParseError.error != QJsonParseError::NoError)
        {
            qCCritical(radioDiscord).nospace()
                << "failed to parse an incoming message with operation code "
                << messageHeader.operationCode << ": "
                << messageParseError.errorString() << " (offset is "
                << messageParseError.offset << ')';

            break;
        }

        switch (messageHeader.operationCode)
        {
            case FRAME:
            {
                if (m_handshakeState != HANDSHAKE_ACTIVE
                    || message["cmd"] != "DISPATCH"
                    || message["evt"] != "READY")
                {
                    break;
                }

                qCInfo(radioDiscord) << "handshake with discord succeeded";

                m_handshakeState = HANDSHAKE_COMPLETE;

                setActivity(m_currentActivity, true);

                break;
            }

            case PING:
            {
                sendMessage({}, PONG);

                break;
            }

            case PONG:
            {
                break;
            }

            case CLOSE:
            {
                m_socket->close();

                break;
            }

            case HANDSHAKE:
            default:
            {
                qCCritical(radioDiscord) << "bad ipc frame";

                m_socket->close();

                break;
            }
        }
    }
}

void Discord::setActivity(const QJsonObject &activity, const bool &force)
{
    if (activity == m_currentActivity && !force)
    {
        return;
    }

    m_currentActivity = activity;

    sendMessage({
        { "cmd","SET_ACTIVITY"   },
        {"args",
         QJsonObject {{"pid", QCoreApplication::applicationPid()},
         {"activity", activity}}}
    });
}

void Discord::setActivity(const QJsonObject &activity)
{
    instance()->setActivity(activity, false);
}

