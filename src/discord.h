#pragma once

#include <QJsonObject>
#include <QLocalSocket>
#include <QLoggingCategory>
#include <QTimer>

Q_DECLARE_LOGGING_CATEGORY(radio_discord)

class Discord : public QObject
{
    Q_OBJECT

private:
    enum HandshakeState
    {
        HandshakeInactive,
        HandshakeActive,
        HandshakeDone
    };

    enum OperationCode
    {
        Handshake,
        Frame,
        Close,
        Ping,
        Pong
    };

    struct MessageHeader
    {
        OperationCode operationCode;

        quint32 payloadSize;
    };

    HandshakeState m_handshakeState = HandshakeInactive;
    QLocalSocket *m_socket = new QLocalSocket(this);
    QTimer *m_reconnectTimer = new QTimer(this);

    QJsonValue m_currentActivity;

    int m_pipeNumber = -1;

    Discord();
    static Discord *instance();

    void sendMessage(QJsonObject message, const OperationCode &operationCode = Frame);
    void handshake();

    void setActivity(const QJsonValue &activity, const bool &force);

    bool pipeExists(const int &pipeNumber);

    void connect();

public:
    static void setActivity(const QJsonValue &activity);
};
