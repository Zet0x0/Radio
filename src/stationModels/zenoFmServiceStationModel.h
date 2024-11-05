#pragma once

#include "serviceStationModel.h"

class ZenoFmServiceStationModel : public ServiceStationModel
{
    Q_OBJECT
    QML_ELEMENT

public slots:
    void search(const QString &query, const bool &newSearch = true) override;

private:
    int m_searchPageNumber = 1;

public:
    void fetchMore(const QModelIndex &parent) override;
};
