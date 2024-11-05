#include "nowPlayingImageProvider.h"
#include "networkAccessManager.h"
#include "player.h"
#include <QJsonArray>

Q_LOGGING_CATEGORY(radio_nowPlayingImageProvider, "radio.nowPlayingImageProvider")

NowPlayingImageProvider::NowPlayingImageProvider()
{
    connect(Player::instance(), &Player::nowPlayingChanged, this,
            &NowPlayingImageProvider::fetchImage);
}

NowPlayingImageProvider *NowPlayingImageProvider::instance()
{
    static NowPlayingImageProvider *instance = new NowPlayingImageProvider;

    return instance;
}

NowPlayingImageProvider *NowPlayingImageProvider::qmlInstance(QQmlEngine *, QJSEngine *)
{
    return instance();
}

const QString NowPlayingImageProvider::currentImageUrl()
{
    return instance()->m_currentImageUrl;
}

void NowPlayingImageProvider::fetchImage(const QString &query)
{
    if (m_pendingReply)
    {
        m_pendingReply->abort();
    }

    setCurrentImageUrl(QString());

    if (query.isEmpty())
    {
        return;
    }

    if (m_accessToken.isEmpty() ||
        m_accessTokenExpirationTimestampMs <= QDateTime::currentMSecsSinceEpoch())
    {
        refreshAccessToken(query);

        return;
    }

    qCDebug(radio_nowPlayingImageProvider) << "requesting image for query" << query;

    QNetworkRequest searchRequest = QNetworkRequest(
        QUrl(QString("https://api.spotify.com/v1/"
                     "search?type=track&q=%0&best_match=true&limit=1&include_external=audio")
                 .arg(query)));
    searchRequest.setRawHeader("Authorization", QString("Bearer %0").arg(m_accessToken).toUtf8());

    QNetworkReply *reply = m_pendingReply = NetworkAccessManager::get(searchRequest);

    connect(reply, &QNetworkReply::finished, this,
            [reply, query, this]
            {
                if (!NetworkAccessManager::shouldParseReply(reply))
                {
                    return;
                }

                const NetworkAccessManager::ParsedReply parsedReply =
                    NetworkAccessManager::parseReply(reply);

                if (parsedReply.error != NetworkAccessManager::NoError)
                {
                    qCCritical(radio_nowPlayingImageProvider).nospace()
                        << "failed to fetch image for query " << query
                        << ": failed to parse response: " << parsedReply.errorString;

                    return;
                }

                const QJsonValue bestMatch =
                    parsedReply.json["best_match"]["items"].toArray().first();

                if (bestMatch.isUndefined())
                {
                    qCCritical(radio_nowPlayingImageProvider).nospace()
                        << "failed to fetch image for query " << query
                        << ": bestMatch.isUndefined() returned true";

                    return;
                }

                const QJsonArray bestMatchImages =
                    bestMatch["album"]["images"].toArray(bestMatch["images"].toArray());

                if (bestMatchImages.isEmpty())
                {
                    qCCritical(radio_nowPlayingImageProvider).nospace()
                        << "failed to fetch image for query " << query
                        << ": bestMatchImages.isEmpty() returned true";

                    return;
                }

                setCurrentImageUrl(
                    bestMatchImages.at(qCeil((bestMatchImages.size() - 1) / 2))["url"].toString());
            });
    connect(reply, &QNetworkReply::errorOccurred, this,
            [reply, query, this]
            {
                qCCritical(radio_nowPlayingImageProvider).nospace()
                    << "failed to request image for query " << query << ": "
                    << reply->errorString();

                if (reply->attribute(QNetworkRequest::HttpStatusCodeAttribute) == 401)
                {
                    refreshAccessToken(query);
                }
            });
    connect(reply, &QNetworkReply::destroyed, this,
            [this]
            {
                m_pendingReply = nullptr;
            });
}

void NowPlayingImageProvider::refreshAccessToken(const QString &pendingQuery)
{
    m_pendingQuery = pendingQuery;

    if (m_refreshingAccessToken)
    {
        return;
    }

    m_refreshingAccessToken = true;

    qCDebug(radio_nowPlayingImageProvider) << "refreshing access token";

    QNetworkReply *reply = NetworkAccessManager::get(
        QNetworkRequest(QUrl("https://open.spotify.com/get_access_token")));

    connect(reply, &QNetworkReply::finished, this,
            [reply, this]
            {
                if (!NetworkAccessManager::shouldParseReply(reply))
                {
                    return;
                }

                m_refreshingAccessToken = false;
                const QString pendingQuery = m_pendingQuery;
                m_pendingQuery = QString();

                const NetworkAccessManager::ParsedReply parsedReply =
                    NetworkAccessManager::parseReply(reply);

                if (parsedReply.error != NetworkAccessManager::NoError)
                {
                    qCCritical(radio_nowPlayingImageProvider)
                        << "failed to refresh access token: failed to parse response:"
                        << parsedReply.errorString;

                    return;
                }

                const QJsonDocument json = parsedReply.json;

                m_accessTokenExpirationTimestampMs =
                    json["accessTokenExpirationTimestampMs"].toInteger();
                m_accessToken = json["accessToken"].toString();

                qCDebug(radio_nowPlayingImageProvider).nospace()
                    << "access token refreshed: " << m_accessToken
                    << " (expiration timestamp ms: " << m_accessTokenExpirationTimestampMs << ')';

                fetchImage(pendingQuery);
            });
    connect(reply, &QNetworkReply::errorOccurred, this,
            [reply, this]
            {
                m_refreshingAccessToken = false;
                m_pendingQuery = QString();

                qCCritical(radio_nowPlayingImageProvider)
                    << "failed to refresh access token:" << reply->errorString();
            });
}

void NowPlayingImageProvider::setCurrentImageUrl(const QString &currentImageUrl)
{
    if (currentImageUrl == m_currentImageUrl)
    {
        return;
    }

    m_currentImageUrl = currentImageUrl;

    qCDebug(radio_nowPlayingImageProvider) << "new value for currentImageUrl:" << currentImageUrl;

    emit currentImageUrlChanged(currentImageUrl);
}
