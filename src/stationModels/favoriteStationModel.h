#pragma once

#include "stationModel.h"

class FavoriteStationModel : public StationModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    FavoriteStationModel();

    QVariant data(const QModelIndex &, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
};
