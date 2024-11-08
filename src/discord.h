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
        Handshake = 0,
        Frame = 1,
        Close = 2,
        Ping = 3,
        Pong = 4
    };

    struct MessageHeader
    {
        OperationCode operationCode;

        quint32 payloadSize;
    };

    HandshakeState m_handshakeState = HandshakeInactive;
    QLocalSocket *m_socket = new QLocalSocket(this);
    QTimer *m_reconnectTimer = new QTimer(this);
    int m_pipeNumber = -1;

    QJsonValue m_currentActivity;

    Discord();
    static Discord *instance();

    void sendMessage(QJsonObject message, const OperationCode &operationCode = Frame);
    void handshake();

    void setActivity(const QJsonValue &activity, const bool &force);

    bool pipeExists(const int &pipeNumber);

    void connect();

public:
    enum ActivityType
    {
        Playing = 0,
        Streaming = 1,
        Listening = 2,
        Watching = 3,
        Custom = 4,
        Competing = 5
    };

    static void setActivity(const QJsonValue &activity);
};
