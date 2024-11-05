#include "favoriteStationModel.h"
#include "../favoritesManager.h"

FavoriteStationModel::FavoriteStationModel()
{
    FavoritesManager *favoritesManager = FavoritesManager::instance();

    connect(favoritesManager, &FavoritesManager::stationRemoved, this,
            [this](const Station &station, const qsizetype &index)
            {
                beginRemoveRows(QModelIndex(), index, index);
                endRemoveRows();
            });
    connect(favoritesManager, &FavoritesManager::stationAdded, this,
            [this](const Station &station, const qsizetype &index)
            {
                beginInsertRows(QModelIndex(), index, index);
                endInsertRows();
            });
}

QVariant FavoriteStationModel::data(const QModelIndex &index, int role) const
{
    return StationModel::data(index, role, FavoritesManager::favorites());
}

int FavoriteStationModel::rowCount(const QModelIndex &parent) const
{
    return (parent.isValid()) ? 0 : FavoritesManager::favorites().size();
}
