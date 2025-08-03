#pragma once

#include <QJsonObject>
#include <QLocalSocket>
#include <QLoggingCategory>
#include <QTimer>

Q_DECLARE_LOGGING_CATEGORY(radioDiscord)

class Discord : public QObject
{
    Q_OBJECT

private:
    // https://github.com/discord/discord-rpc/blob/963aa9f3e5ce81a4682c6ca3d136cddda614db33/src/rpc_connection.h#L17
    enum OperationCode
    {
        HANDSHAKE = 0,
        FRAME = 1,
        CLOSE = 2,
        PING = 3,
        PONG = 4
    };

    struct MessageHeader
    {
        OperationCode operationCode;
        quint32 payloadSize;
    };

    enum HandshakeState
    {
        HANDSHAKE_INACTIVE = 0,
        HANDSHAKE_ACTIVE = 1,
        HANDSHAKE_COMPLETE = 2
    };

    int m_pipe = -1;
    QLocalSocket *m_socket = new QLocalSocket(this);
    QTimer *m_reconnectTimer = new QTimer(this);
    HandshakeState m_handshakeState = HANDSHAKE_INACTIVE;

    QJsonObject m_currentActivity;

    Discord();
    static Discord *instance();

    bool pipeExists(const int &pipe);
    void connect();
    void handshake();
    void sendMessage(QJsonObject message,
                     const OperationCode &operationCode = FRAME);
    void processDataFromSocket();

    void setActivity(const QJsonObject &activity, const bool &force);

public:
    // https://discord.com/developers/docs/events/gateway-events#activity-object-activity-types
    enum ActivityType
    {
        PLAYING = 0,
        STREAMING = 1,
        LISTENING = 2,
        WATCHING = 3,
        CUSTOM = 4,
        COMPETING = 5
    };

    static void setActivity(const QJsonObject &activity);
};
