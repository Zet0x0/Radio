#include "favoritesManager.h"
#include "utilities.h"
#include <QDir>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

Q_LOGGING_CATEGORY(radio_favoritesManager, "radio.favoritesManager")

FavoritesManager::FavoritesManager()
{
    qCDebug(radio_favoritesManager) << "working with file" << favoritesFilePath();

    synchronizeWithFile();
}

FavoritesManager *FavoritesManager::instance()
{
    static FavoritesManager *instance = new FavoritesManager;

    return instance;
}

FavoritesManager *FavoritesManager::qmlInstance(QQmlEngine *, QJSEngine *)
{
    return instance();
}

bool FavoritesManager::writeToFile(const QList<Station> &favorites)
{
    qCDebug(radio_favoritesManager) << "writing favorites to file";

    QFile favoritesFile(favoritesFilePath());

    if (!favoritesFile.open(QFile::WriteOnly | QFile::Text))
    {
        const QString errorString = favoritesFile.errorString();

        qCCritical(radio_favoritesManager) << "failed to open the file for write:" << errorString;

        Utilities::requestMessageDialog("Favorites Save Error",
                                        "Failed to open the file for write.", errorString);

        return false;
    }

    QJsonArray jsonifiedFavorites;

    for (const Station &station : favorites)
    {
        jsonifiedFavorites << QJsonObject{
            {"streamUrls", QJsonArray::fromStringList(station.streamUrls)},
            {"imageUrl",   station.imageUrl                              },
            {"subtitle",   station.subtitle                              },
            {"title",      station.title                                 }
        };
    }

    switch (favoritesFile.write(QJsonDocument(jsonifiedFavorites).toJson()))
    {
        case 0:
        {
            qCCritical(radio_favoritesManager)
                << "failed to write favorites to the file: bytesWritten == 0";

            Utilities::requestMessageDialog("Favorites Write Error",
                                            "No bytes were written to the file.");

            return false;
        }

        case -1:
        {
            const QString errorString = favoritesFile.errorString();

            qCCritical(radio_favoritesManager)
                << "failed to write favorites to the file:" << errorString;

            Utilities::requestMessageDialog("Favorites Write Error",
                                            "Failed to write favorites to the file.", errorString);

            return false;
        }

        default:
        {
            return true;
        }
    }
}

const QString FavoritesManager::favoritesFilePath()
{
    return QDir::toNativeSeparators(QFileInfo("favorites.json").absoluteFilePath());
}

const QList<Station> FavoritesManager::favorites()
{
    return instance()->m_favorites;
}

void FavoritesManager::synchronizeWithFile()
{
    QFile favoritesFile(favoritesFilePath());

    if (!favoritesFile.exists())
    {
        return;
    }

    qCDebug(radio_favoritesManager) << "synchronizing favorites with file";

    if (!favoritesFile.open(QFile::ReadOnly | QFile::Text))
    {
        const QString errorString = favoritesFile.errorString();

        qCCritical(radio_favoritesManager) << "failed to open the file for read:" << errorString;

        Utilities::requestMessageDialog("Favorites Synchronization Error",
                                        "Failed to open the file for read.", errorString);

        return;
    }

    QString jsonParseErrorString;
    const QJsonDocument json = Utilities::parseJson(favoritesFile.readAll(), jsonParseErrorString);

    if (favoritesFile.size() > 0 && !jsonParseErrorString.isEmpty())
    {
        qCCritical(radio_favoritesManager)
            << "failed to synchronize favorites with file: failed to parse the file:"
            << jsonParseErrorString;

        Utilities::requestMessageDialog("Favorites Synchronization Error",
                                        "Failed to parse the file.", jsonParseErrorString);

        return;
    }

    const QJsonArray loadedEntries = json.array();
    const qsizetype loadedEntriesSize = loadedEntries.size();

    qCDebug(radio_favoritesManager) << "loaded" << loadedEntriesSize << "entries from the file";

    QList<Station> newFavorites;

    for (const QJsonValue &entry : loadedEntries)
    {
        const Station station = Utilities::stationFromJson(entry.toObject());

        if (!newFavorites.contains(station))
        {
            newFavorites << station;
        }
    }

    const qsizetype newFavoritesSize = newFavorites.size();

    if (newFavoritesSize != loadedEntriesSize)
    {
        qCWarning(radio_favoritesManager)
            << "working only with"
            << "items from the loaded" << loadedEntriesSize << "entries";
    }

    const QSet<Station> newFavoritesSet(newFavorites.constBegin(), newFavorites.constEnd());
    const QSet<Station> oldFavoritesSet(m_favorites.constBegin(), m_favorites.constEnd());

    const QSet<Station> removedStations = oldFavoritesSet - newFavoritesSet;
    const QSet<Station> addedStations = newFavoritesSet - oldFavoritesSet;

    for (const Station &removedStation : removedStations)
    {
        qCDebug(radio_favoritesManager) << "station removed:" << removedStation;

        emit stationRemoved(removedStation, m_favorites.indexOf(removedStation));
    }

    for (const Station &addedStation : addedStations)
    {
        qCDebug(radio_favoritesManager) << "station added:" << addedStation;

        emit stationAdded(addedStation, newFavorites.indexOf(addedStation));
    }

    m_favorites = newFavorites;

    emit favoritesChanged(newFavorites);
}

void FavoritesManager::removeStation(const Station &station)
{
    if (!m_favorites.contains(station))
    {
        return;
    }

    qCDebug(radio_favoritesManager) << "removing station:" << station;

    const qsizetype stationIndex = m_favorites.indexOf(station);
    QList<Station> newFavorites = m_favorites;

    newFavorites.removeAt(stationIndex);

    if (!writeToFile(newFavorites))
    {
        return;
    }

    m_favorites.removeAt(stationIndex);

    emit stationRemoved(station, stationIndex);

    emit favoritesChanged(newFavorites);
}

void FavoritesManager::addStation(const Station &station)
{
    if (m_favorites.contains(station))
    {
        return;
    }

    qCDebug(radio_favoritesManager) << "adding station:" << station;

    QList<Station> newFavorites = m_favorites;

    newFavorites << station;

    if (!writeToFile(newFavorites))
    {
        return;
    }

    m_favorites << station;

    emit stationAdded(station, newFavorites.size() - 1);

    emit favoritesChanged(newFavorites);
}
