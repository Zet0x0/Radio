#include "discord.h"
#include "utilities.h"
#include <QFile>
#include <QGuiApplication>
#include <QJsonDocument>

Q_LOGGING_CATEGORY(radio_discord, "radio.discord")

Discord::Discord()
{
    QObject::connect(m_socket, &QLocalSocket::readyRead, this,
                     [this]
                     {
                         const size_t messageHeaderSize = sizeof(MessageHeader);

                         while (m_socket->bytesAvailable() > messageHeaderSize)
                         {
                             const QByteArray rawMessageHeader = m_socket->read(messageHeaderSize);
                             const MessageHeader messageHeader =
                                 *reinterpret_cast<const MessageHeader *>(rawMessageHeader.data());

                             QString messageParseErrorString;
                             const QJsonDocument message =
                                 Utilities::parseJson(m_socket->read(messageHeader.payloadSize),
                                                      messageParseErrorString);

                             const OperationCode operationCode = messageHeader.operationCode;

                             if (!messageParseErrorString.isEmpty())
                             {
                                 qCCritical(radio_discord).nospace()
                                     << "failed to parse an incoming message with operation code "
                                     << operationCode << ": " << messageParseErrorString;

                                 break;
                             }

                             qCDebug(radio_discord).nospace()
                                 << "incoming message with operation code " << operationCode << ": "
                                 << message;

                             switch (operationCode)
                             {
                                 case Frame:
                                 {
                                     if (m_handshakeState != HandshakeActive ||
                                         message["cmd"] != "DISPATCH" || message["evt"] != "READY")
                                     {
                                         break;
                                     }

                                     qCDebug(radio_discord) << "handshake done";

                                     m_handshakeState = HandshakeDone;

                                     if (!m_currentActivity.isNull())
                                     {
                                         setActivity(m_currentActivity, true);
                                     }

                                     break;
                                 }

                                 case Ping:
                                 {
                                     sendMessage({}, Pong);

                                     break;
                                 }

                                 case Pong:
                                 {
                                     break;
                                 }

                                 case Close:
                                 {
                                     m_socket->close();

                                     break;
                                 }

                                 case Handshake:
                                 default:
                                 {
                                     qCCritical(radio_discord) << "bad ipc frame";

                                     m_socket->close();

                                     break;
                                 }
                             }
                         }
                     });
    QObject::connect(m_socket, &QLocalSocket::stateChanged, this,
                     [this](QLocalSocket::LocalSocketState state)
                     {
                         switch (state)
                         {
                             case QLocalSocket::UnconnectedState:
                             {
                                 qCDebug(radio_discord) << "connection closed";

                                 m_handshakeState = HandshakeInactive;

                                 m_reconnectTimer->start();

                                 break;
                             }

                             case QLocalSocket::ConnectingState:
                             {
                                 qCDebug(radio_discord) << "establishing connection...";

                                 break;
                             }

                             case QLocalSocket::ConnectedState:
                             {
                                 qCDebug(radio_discord) << "connection established";

                                 m_reconnectTimer->stop();

                                 handshake();

                                 break;
                             }

                             case QLocalSocket::ClosingState:
                             {
                                 qCDebug(radio_discord) << "closing connection...";

                                 break;
                             }
                         }
                     });
    QObject::connect(m_socket, &QLocalSocket::errorOccurred, this,
                     [this]
                     {
                         qCCritical(radio_discord) << "socket emitted the errorOccurred signal:"
                                                   << m_socket->errorString();
                     });
    QObject::connect(m_reconnectTimer, &QTimer::timeout, this,
                     [this]
                     {
                         if (m_socket->state() != QLocalSocket::UnconnectedState)
                         {
                             return;
                         }

                         qCDebug(radio_discord) << "trying to reconnect";

                         connect();
                     });

    qAddPostRoutine(
        []
        {
            instance()->m_socket->close();
        });

    m_reconnectTimer->setInterval(1000);
}

Discord *Discord::instance()
{
    static Discord *instance = new Discord;

    return instance;
}

void Discord::sendMessage(QJsonObject message, const OperationCode &operationCode)
{
    if (!m_socket->isOpen())
    {
        connect();

        return;
    }

    const QString nonce = QUuid::createUuid().toString(QUuid::WithoutBraces);
    message["nonce"] = nonce;

    qCDebug(radio_discord).nospace()
        << "sending a message with operation code " << operationCode << ": " << message;

    const QByteArray payload = QJsonDocument(message).toJson(QJsonDocument::Compact);
    const MessageHeader messageHeader = MessageHeader{static_cast<OperationCode>(operationCode),
                                                      static_cast<quint32>(payload.size())};

    switch (m_socket->write(QByteArray::fromRawData(reinterpret_cast<const char *>(&messageHeader),
                                                    sizeof(MessageHeader)) +
                            payload))
    {
        case 0:
        {
            qCCritical(radio_discord).nospace() << "failed to send message with operation code "
                                                << operationCode << ", with nonce " << nonce << ": "
                                                << "bytesWritten == 0";

            break;
        }

        case -1:
        {
            qCCritical(radio_discord).nospace()
                << "failed to send message with operation code " << operationCode << ", with nonce "
                << nonce << ": " << m_socket->errorString();

            break;
        }

        default:
        {
            qCDebug(radio_discord).nospace()
                << "outgoing message with operation code " << operationCode << ": " << message;

            break;
        }
    }
}

bool Discord::pipeExists(const int &pipeNumber)
{
    return QFile::exists(QString("\\\\.\\pipe\\discord-ipc-%0").arg(QString::number(pipeNumber)));
}

void Discord::setActivity(const QJsonValue &activity)
{
    instance()->setActivity(activity, false);
}

void Discord::handshake()
{
    qCDebug(radio_discord) << "handshake active";

    m_handshakeState = HandshakeActive;

    sendMessage(
        {
            {"client_id", "1071759411586023485"},
            {"v",         1                    }
    },
        Handshake);
}

void Discord::connect()
{
    if (m_pipeNumber == -1 || !pipeExists(m_pipeNumber))
    {
        qCDebug(radio_discord) << "looking for available pipes";

        m_pipeNumber = -1;

        for (int i = 0; i < 10; ++i)
        {
            if (pipeExists(i))
            {
                m_pipeNumber = i;

                break;
            }
        }

        if (m_pipeNumber == -1)
        {
            qCCritical(radio_discord) << "couldn't find any available pipes";

            return;
        }

        qCDebug(radio_discord) << "choosing pipe" << m_pipeNumber;
    }

    m_socket->connectToServer(QString("discord-ipc-%0").arg(QString::number(m_pipeNumber)));
}

void Discord::setActivity(const QJsonValue &activity, const bool &force)
{
    if (activity == m_currentActivity && !force)
    {
        return;
    }

    qCDebug(radio_discord) << "updating current activity to:" << activity;

    m_currentActivity = activity;

    sendMessage({
        {"args", QJsonObject{{"pid", QGuiApplication::applicationPid()}, {"activity", activity}}},
        {"cmd",  "SET_ACTIVITY"                                                                 }
    });
}
