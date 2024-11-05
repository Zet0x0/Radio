#include "networkAccessManager.h"
#include "utilities.h"
#include <QNetworkReply>

NetworkAccessManager *NetworkAccessManager::instance()
{
    static NetworkAccessManager *instance = new NetworkAccessManager;

    return instance;
}

const NetworkAccessManager::ParsedReply NetworkAccessManager::parseReply(QNetworkReply *reply,
                                                                         const bool &parseJson)
{
    ParsedReply parsedReply;

    parsedReply.content = QByteArray();
    parsedReply.json = QJsonDocument();
    parsedReply.setError(NoError, QString());

    const QByteArray content = reply->readAll();

    if (content.isEmpty())
    {
        parsedReply.setError(ContentEmpty, "Server returned no data.");

        return parsedReply;
    }

    if (!parseJson)
    {
        parsedReply.content = content;

        return parsedReply;
    }

    QString jsonParseErrorString;
    const QJsonDocument json = Utilities::parseJson(content, jsonParseErrorString);

    if (jsonParseErrorString.isEmpty())
    {
        parsedReply.json = json;
    }
    else
    {
        parsedReply.setError(JsonParseError, jsonParseErrorString);
    }

    return parsedReply;
}

bool NetworkAccessManager::shouldParseReply(QNetworkReply *reply)
{
    return reply->error() == QNetworkReply::NoError;
}

QNetworkReply *NetworkAccessManager::get(QNetworkRequest request, const bool &autoDelete)
{
    request.setAttribute(QNetworkRequest::AutoDeleteReplyOnFinishAttribute, autoDelete);

    return instance()->m_networkAccessManager->get(request);
}

void NetworkAccessManager::ParsedReply::setError(const RequestError &error,
                                                 const QString &errorString)
{
    this->error = error;
    this->errorString = errorString;
}
