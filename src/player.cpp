#include "player.h"

#include "mpveventmanager.h"

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

Player::Player()
{
    MpvEventManager *mpvEventManager = MpvEventManager::instance();

    connect(mpvEventManager, &MpvEventManager::nowPlayingChanged, this, &Player::setNowPlaying);
    connect(mpvEventManager, &MpvEventManager::elapsedChanged, this, &Player::setElapsed);
    connect(mpvEventManager, &MpvEventManager::playerStateChanged, this, &Player::setState);
    connect(mpvEventManager, &MpvEventManager::volumeChanged, this, &Player::setVolume);
    connect(mpvEventManager, &MpvEventManager::mutedChanged, this, &Player::setMuted);
}

QString Player::nowPlaying() const
{
    return m_nowPlaying;
}

void Player::setNowPlaying(const QString &newNowPlaying)
{
    if (m_nowPlaying == newNowPlaying)
    {
        return;
    }

    m_nowPlaying = newNowPlaying;

    emit nowPlayingChanged();
}

qint64 Player::elapsed() const
{
    return m_elapsed;
}

void Player::setElapsed(const qint64 &newElapsed)
{
    if (m_elapsed == newElapsed)
    {
        return;
    }

    m_elapsed = newElapsed;

    emit elapsedChanged();
}

PlayerState Player::state() const
{
    return m_state;
}

void Player::setState(const PlayerState &newState)
{
    if (m_state == newState)
    {
        return;
    }

    m_state = newState;

    emit stateChanged();
}

qreal Player::volume() const
{
    return m_volume;
}

void Player::setVolume(const qreal &newVolume)
{
    if (qFuzzyCompare(m_volume, newVolume))
    {
        return;
    }

    m_volume = newVolume;

    emit volumeChanged();
}

bool Player::muted() const
{
    return m_muted;
}

void Player::setMuted(const bool &newMuted)
{
    if (m_muted == newMuted)
    {
        return;
    }

    m_muted = newMuted;

    emit mutedChanged();
}
