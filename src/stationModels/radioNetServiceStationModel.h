#pragma once

#include "serviceStationModel.h"

class RadioNetServiceStationModel : public ServiceStationModel
{
    Q_OBJECT
    QML_ELEMENT

public slots:
    void search(const QString &, const bool &newSearch = true) override;

private:
    int m_searchOffset = 0;

public:
    void fetchMore(const QModelIndex &parent) override;
};
