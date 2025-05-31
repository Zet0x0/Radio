#pragma once

#include "station.h"

enum PlayerState
{
    STOPPED,
    LOADING,
    PLAYING
};

class Player : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Station *station READ station WRITE setStation NOTIFY stationChanged FINAL)

public:
    static Player *instance();

    Station *station() const;
    void setStation(Station *newStation);

signals:
    void stationChanged();

private:
    Station *m_station;
};
