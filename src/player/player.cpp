#include "player.h"

#include "mpveventmanager.h"

Q_LOGGING_CATEGORY(radioPlayer, "radio.player")

Player *Player::instance()
{
    static Player *instance = new Player;

    return instance;
}

Player *Player::create(QQmlEngine *, QJSEngine *)
{
    return instance();
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

    qCInfo(radioPlayer) << "station changed:" << *m_station;

    emit stationChanged();
}

Player::Player()
{
    MpvEventManager *mpvEventManager = MpvEventManager::instance();
    connect(mpvEventManager,
            &MpvEventManager::nowPlayingChanged,
            this,
            &Player::setNowPlaying);
    connect(mpvEventManager,
            &MpvEventManager::elapsedChanged,
            this,
            &Player::setElapsed);
    connect(mpvEventManager,
            &MpvEventManager::playerStateChanged,
            this,
            &Player::setState);
    connect(mpvEventManager,
            &MpvEventManager::volumeChanged,
            this,
            &Player::setVolume);
    connect(mpvEventManager,
            &MpvEventManager::mutedChanged,
            this,
            &Player::setMuted);
}

QString Player::nowPlaying() const
{
    return m_nowPlaying;
}

void Player::setNowPlaying(QString newNowPlaying)
{
    newNowPlaying = newNowPlaying.trimmed();

    if (!newNowPlaying.isEmpty())
    {
        QVariant filename;

        if (m_mpv->getProperty("filename", &filename) == MPV_ERROR_SUCCESS
            && newNowPlaying == filename)
        {
            newNowPlaying.clear();
        }
    }

    if (m_nowPlaying == newNowPlaying)
    {
        return;
    }

    m_nowPlaying = newNowPlaying;

    qCInfo(radioPlayer) << "nowPlaying changed:" << m_nowPlaying;

    m_mpv->setProperty("title",
                       (m_nowPlaying.isEmpty())
                           ? tr("Radio")
                           : QString(tr("%0 – Radio")).arg(m_nowPlaying));

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

Player::State Player::state() const
{
    return m_state;
}

void Player::setState(const Player::State &newState)
{
    if (m_state == newState)
    {
        return;
    }

    m_state = newState;

    qCInfo(radioPlayer) << "state changed:" << m_state;

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

    qCInfo(radioPlayer) << "volume changed:" << m_volume;

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

    qCInfo(radioPlayer) << "muted changed:" << m_muted;

    emit mutedChanged();
}
