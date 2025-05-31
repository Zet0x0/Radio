#include "player.h"

Player *Player::instance()
{
    static Player *instance = new Player;

    return instance;
}

Station *Player::station() const
{
    return m_station;
}

void Player::setStation(Station *newStation)
{
    if (m_station == newStation)
    {
        return;
    }

    m_station = newStation;

    emit stationChanged();
}
