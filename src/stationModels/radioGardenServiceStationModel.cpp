#include "radioGardenServiceStationModel.h"
#include "../networkAccessManager.h"
#include "../utilities.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QNetworkReply>

void RadioGardenServiceStationModel::search(const QString &query, const bool &)
{
    setSearching(true);

    QNetworkReply *reply = NetworkAccessManager::get(
        QNetworkRequest(QUrl(QString("https://radio.garden/api/search/secure?q=%0").arg(query))));

    connect(reply, &QNetworkReply::finished, this,
            [reply, this]
            {
                if (!NetworkAccessManager::shouldParseReply(reply))
                {
                    return;
                }

                beginResetModel();

                m_stations.clear();

                const NetworkAccessManager::ParsedReply parsedReply =
                    NetworkAccessManager::parseReply(reply);

                if (parsedReply.error != NetworkAccessManager::NoError)
                {
                    reportSearchError(parsedReply.errorString);

                    endResetModel();

                    return;
                }

                const QJsonArray hits = parsedReply.json["hits"]["hits"].toArray();

                for (const QJsonValue &hit : hits)
                {
                    const QJsonObject hitSource = hit["_source"].toObject();

                    if (hitSource["type"] != "channel")
                    {
                        continue;
                    }

                    const QString channelId =
                        hitSource["url"].toString().split("/", Qt::SkipEmptyParts).last();

                    if (channelId.isEmpty())
                    {
                        continue;
                    }

                    Station station = Utilities::stationFromJson(hitSource);

                    station.streamUrls = {
                        QString("https://radio.garden/api/ara/content/listen/%0/channel.mp3")
                            .arg(channelId)};

                    m_stations << station;
                }

                endResetModel();

                emit finished();
            });
    connect(reply, &QNetworkReply::errorOccurred, this,
            [this, reply]
            {
                beginResetModel();

                m_stations.clear();

                endResetModel();

                reportSearchError(reply->errorString());
            });
}
