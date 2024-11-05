#include "zenoFmServiceStationModel.h"
#include "../networkAccessManager.h"
#include "../utilities.h"
#include <QJsonArray>
#include <QNetworkReply>

void ZenoFmServiceStationModel::search(const QString &query, const bool &newSearch)
{
    setSearching(true);

    if (newSearch)
    {
        m_currentSearchQuery = query;
        m_searchReachedEnd = false;
        m_searchPageNumber = 1;
    }

    QNetworkReply *reply = NetworkAccessManager::get(
        QNetworkRequest(QUrl(QString("https://zeno.fm/api/stations/?query=%0&limit=20&page=%1")
                                 .arg(query, QString::number(m_searchPageNumber)))));

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

                const QJsonArray results = parsedReply.json.array();
                QList<Station> finalStationList;

                for (const QJsonValue &result : results)
                {
                    Station station;

                    station.title = Utilities::sanitizeString(result["name"].toString());
                    station.streamUrls = {result["url"].toString()};
                    station.imageUrl = result["logo"].toString();
                    station.subtitle = QString();

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

                m_searchReachedEnd = results.size() < 20;

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

void ZenoFmServiceStationModel::fetchMore(const QModelIndex &parent)
{
    if (parent.isValid())
    {
        return;
    }

    ++m_searchPageNumber;

    search(m_currentSearchQuery, false);
}
