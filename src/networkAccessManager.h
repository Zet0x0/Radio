#pragma once

#include <QJsonDocument>
#include <QNetworkAccessManager>

class NetworkAccessManager : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *m_networkAccessManager = new QNetworkAccessManager(this);

    static NetworkAccessManager *instance();

public:
    enum RequestError
    {
        NoError,
        ContentEmpty,
        JsonParseError
    };

    struct ParsedReply
    {
        QByteArray content;
        QJsonDocument json;

        RequestError error;
        QString errorString;

        void setError(const RequestError &, const QString &errorString);
    };

    static const ParsedReply parseReply(QNetworkReply *, const bool &parseJson = true);
    static bool shouldParseReply(QNetworkReply *);

    static QNetworkReply *get(QNetworkRequest, const bool &autoDelete = true);
};
