#include "radioNetServiceStationModel.h"
#include "../networkAccessManager.h"
#include "../utilities.h"
#include <QJsonArray>
#include <QNetworkReply>

void RadioNetServiceStationModel::search(const QString &query, const bool &newSearch)
{
    setSearching(true);

    if (newSearch)
    {
        m_currentSearchQuery = query;
        m_searchReachedEnd = false;
        m_searchOffset = 0;
    }

    QNetworkReply *reply = NetworkAccessManager::get(QNetworkRequest(
        QUrl(QString("https://prod.radio-api.net/stations/search?query=%0&count=20&offset=%1")
                 .arg(query, QString::number(m_searchOffset)))));

    connect(reply, &QNetworkReply::finished, this,
            [this, newSearch, reply]
            {
                if (!NetworkAccessManager::shouldParseReply(reply))
                {
                    return;
                }

                if (newSearch)
                {
                    beginResetModel();

                    m_stations.clear();
                }

                const NetworkAccessManager::ParsedReply parsedReply =
                    NetworkAccessManager::parseReply(reply);

                if (parsedReply.error != NetworkAccessManager::NoError)
                {
                    reportSearchError(parsedReply.errorString);

                    if (newSearch)
                    {
                        endResetModel();
                    }

                    return;
                }

                const QJsonArray playables = parsedReply.json["playables"].toArray();
                QList<Station> finalStationList;

                for (const QJsonValue &playable : playables)
                {
                    QString imageUrl;

                    const QString logo100x100 = playable["logo100x100"].toString();
                    const QString logo300x300 = playable["logo300x300"].toString();
                    const QString logo630x630 = playable["logo630x630"].toString();

                    if (!logo100x100.isEmpty())
                    {
                        imageUrl = logo100x100;
                    }
                    else if (!logo300x300.isEmpty())
                    {
                        imageUrl = logo300x300;
                    }
                    else if (!logo630x630.isEmpty())
                    {
                        imageUrl = logo630x630;
                    }

                    QStringList streamUrls;
                    const QJsonArray streams = playable["streams"].toArray();

                    for (const QJsonValue &stream : streams)
                    {
                        streamUrls << stream["url"].toString();
                    }

                    const QString country = playable["country"].toString();
                    const QString city = playable["city"].toString();

                    Station station;

                    station.subtitle = Utilities::sanitizeString(
                        (country.isEmpty() || city.isEmpty())
                            ? ((country.isEmpty()) ? city : country)
                            : QString("%0, %1").arg(playable["city"].toString(),
                                                    playable["country"].toString()));
                    station.title = Utilities::sanitizeString(playable["name"].toString());
                    station.streamUrls = streamUrls;
                    station.imageUrl = imageUrl;

                    finalStationList << station;
                }

                if (!newSearch)
                {
                    const int rowCount = this->rowCount();

                    beginInsertRows(QModelIndex(), rowCount,
                                    rowCount + finalStationList.size() - 1);
                }

                m_stations << finalStationList;

                if (newSearch)
                {
                    endResetModel();
                }
                else
                {
                    endInsertRows();
                }

                m_searchReachedEnd = playables.size() < 20;

                emit finished();
            });
    connect(reply, &QNetworkReply::errorOccurred, this,
            [this, reply, newSearch]
            {
                if (newSearch)
                {
                    beginResetModel();

                    m_stations.clear();

                    endResetModel();
                }

                reportSearchError(reply->errorString());
            });
}

void RadioNetServiceStationModel::fetchMore(const QModelIndex &parent)
{
    if (parent.isValid())
    {
        return;
    }

    m_searchOffset += 20;

    search(m_currentSearchQuery, false);
}
