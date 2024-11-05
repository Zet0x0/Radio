#pragma once

#include "serviceStationModel.h"

class RadioGardenServiceStationModel : public ServiceStationModel
{
    Q_OBJECT
    QML_ELEMENT

public slots:
    void search(const QString &, const bool &newSearch = true) override;
};
