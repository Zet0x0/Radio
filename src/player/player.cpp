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

    m_station->deleteLater();

    m_station = newStation;

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

qint16 Player::volume() const
{
    return m_volume;
}

void Player::setVolume(const qint16 &newVolume)
{
    if (m_volume == newVolume)
    {
        return;
    }

    if (m_mpv->setVolume(newVolume))
    {
        m_volume = newVolume;
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

    emit mutedChanged();
}

void Player::play()
{
    const int result = m_mpv->play(m_station->streamUrl());

    if (result != MPV_ERROR_SUCCESS)
    {
        emit playbackErrorOccurred(result, QPrivateSignal());
    }
}

void Player::stop()
{
    const int result = m_mpv->stop();

    if (result == MPV_ERROR_SUCCESS)
    {
        return;
    }

    qCCritical(radioPlayer)
        << "the stop command mysteriously failed with error code" << result;

    emit messageDialogRequested(
        tr("Command Failed"),
        tr("The stop command (somehow) failed:\n\n%0 (code %1)")
            .arg(mpv_error_string(result), QString::number(result)),
        false);
}

Player::Player()
{
    MpvEventManager *mpvEventManager = MpvEventManager::instance();

    connect(mpvEventManager,
            &MpvEventManager::playbackErrorOccurred,
            this,
            [this](const int &errorCode)
            {
                emit playbackErrorOccurred(errorCode, QPrivateSignal());
            });
    connect(m_mpv,
            &Mpv::initializationErrorOccurred,
            this,
            [this](const int &errorCode)
            {
                qCCritical(radioPlayer)
                    << "mpv failed to initialize with error code" << errorCode;

                emit messageDialogRequested(
                    tr("Initialization Error"),
                    tr("MPV failed to initialize:\n\n%0 (code %1)")
                        .arg(mpv_error_string(errorCode),
                             QString::number(errorCode)),
                    true);
            });
    connect(this,
            &Player::playbackErrorOccurred,
            this,
            [this](const int &errorCode)
            {
                qCCritical(radioPlayer)
                    << "station playback failed with error code" << errorCode;

                emit messageDialogRequested(
                    tr("Playback Error"),
                    tr("An error has occurred trying to play the "
                       "station:\n\n%0 (code %1)")
                        .arg(mpv_error_string(errorCode),
                             QString::number(errorCode)),
                    false);
            });

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

    // TODO: remove this when done testing
    setStation(
        new Station("", "", "https://stream.rcs.revma.com/1a6hdnzbebuvv"));
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

    emit stateChanged();
}
