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
                           : tr("%0 – Radio").arg(m_nowPlaying));

    emit nowPlayingChanged();
}

qint64 Player::elapsed() const
{
    return m_elapsed;
}

Player::State Player::state() const
{
    return m_state;
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

    if (m_mpv->setVolume(newVolume))
    {
        m_volume = newVolume;

        qCInfo(radioPlayer) << "volume changed:" << m_volume;
    }

    emit volumeChanged();
}

bool Player::muted() const
{
    return m_muted;
}

void Player::setMuted(const bool &newMuted)
{
    if (m_muted == newMuted || !m_mpv->setMuted(newMuted))
    {
        return;
    }

    m_muted = newMuted;

    qCInfo(radioPlayer) << "muted changed:" << m_muted;

    emit mutedChanged();
}

qreal Player::maxVolume() const
{
    return m_maxVolume;
}

void Player::play()
{
    m_mpv->play(m_station->streamUrl());
}

void Player::stop()
{
    m_mpv->stop();
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
            &MpvEventManager::maxVolumeChanged,
            this,
            &Player::setMaxVolume);

    {
        QVariant rawMaxVolume;
        qreal maxVolume = 100.0;

        bool ok = false;

        if (m_mpv->getProperty("volume-max", &rawMaxVolume)
            == MPV_ERROR_SUCCESS)
        {
            maxVolume = rawMaxVolume.toReal(&ok);
        }

        setMaxVolume(maxVolume);

        if (!ok)
        {
            qCWarning(radioPlayer).nospace()
                << "failed to retrieve volume-max property (raw, returned "
                   "value is: "
                << rawMaxVolume << ')';
        }
    }

    // TODO: remove this when done testing
    setStation(
        new Station("test station",
                    "https://cdn-images.dzcdn.net/images/cover/"
                    "1fc4079b43b72e6c422dec12caae2407/0x1900-000000-80-0-0.jpg",
                    "https://stream.zeno.fm/z6nrb967wqjvv"));
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

void Player::setMaxVolume(const qreal &newMaxVolume)
{
    if (qFuzzyCompare(m_maxVolume, newMaxVolume))
    {
        return;
    }

    m_maxVolume = newMaxVolume;

    qCInfo(radioPlayer) << "maxVolume changed:" << m_maxVolume;

    emit maxVolumeChanged();
}
