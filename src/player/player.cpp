#include "player.h"

#include "../dialogcontroller.h"
#include "../discord.h"
#include "mpveventmanager.h"

#include <QJsonArray>

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
                           : tr("%0 - Radio").arg(m_nowPlaying));

    qCInfo(radioPlayer) << "nowPlaying changed:" << m_nowPlaying;

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

    if (newVolume > 0)
    {
        setMuted(false);

        if (m_muted)
        {
            qCWarning(radioPlayer) << "volume was not set to" << newVolume
                                   << "because muted didn't change to false";

            return;
        }
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

void Player::playFromUrl(const QString &url)
{
    setStation(new Station(QString(), QString(), url));
    play();
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

    DialogController::requestMessageDialog(
        tr("Command Failed"),
        tr("The stop command (somehow) failed:\n\n%0 (code %1)")
            .arg(mpv_error_string(result), QString::number(result)),
        false);
}

void Player::initialize()
{
    if (m_initialized)
    {
        qCWarning(radioPlayer)
            << "attempted to do Player::initialize while m_initialized is true";

        return;
    }

    const int mpvInitializationResult = m_mpv->initialize();

    if (mpvInitializationResult != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioPlayer) << "mpv failed to initialize with error code"
                                << mpvInitializationResult;

        DialogController::requestMessageDialog(
            tr("Initialization Error"),
            tr("MPV failed to initialize:\n\n%0 (code %1)")
                .arg(mpv_error_string(mpvInitializationResult),
                     QString::number(mpvInitializationResult)),
            true);

        return;
    }

    MpvEventManager *mpvEventManager = MpvEventManager::instance();

    connect(mpvEventManager,
            &MpvEventManager::playbackErrorOccurred,
            this,
            [this](const int &errorCode)
            {
                emit playbackErrorOccurred(errorCode, QPrivateSignal());
            });
    connect(this,
            &Player::playbackErrorOccurred,
            this,
            [this](const int &errorCode)
            {
                qCCritical(radioPlayer)
                    << "station playback failed with error code" << errorCode;

                DialogController::requestMessageDialog(
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
    setStation(new Station(
        "NRJ+",
        "https://i.ytimg.com/vi/kfmstlM3tmU/"
        "maxresdefault.jpg?sqp=-oaymwEmCIAKENAF8quKqQMa8AEB-AH-"
        "CYAC0AWKAgwIABABGH8gGih8MA8=&rs=AOn4CLCBGyBnfBCxOIKTYDYB0TKDQSYhzA",
        "https://stream.rcs.revma.com/1a6hdnzbebuvv"));

    setInitialized(true);

    qCInfo(radioPlayer) << "initialized";
}

bool Player::initialized() const
{
    return m_initialized;
}

Player::Player()
{
    connect(m_discordActivityTimer,
            &QTimer::timeout,
            this,
            &Player::updateDiscordActivity);

    m_discordActivityTimer->setInterval(1000);
    m_discordActivityTimer->start();
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

    if (newState == PLAYING)
    {
        m_startedListeningAt = QDateTime::currentSecsSinceEpoch();
    }
    else
    {
        m_startedListeningAt = -1;
    }

    m_state = newState;

    qCInfo(radioPlayer) << "new state:" << m_state;

    emit stateChanged();
}

void Player::setInitialized(const bool &newInitialized)
{
    if (m_initialized == newInitialized)
    {
        return;
    }

    m_initialized = newInitialized;

    emit initializedChanged();
}

void Player::updateDiscordActivity()
{
    if (m_state != PLAYING)
    {
        Discord::setActivity(QJsonValue());

        return;
    }

    QJsonObject activity;

    QString details = m_station->name();
    QString state = m_nowPlaying;
    QString largeImage = m_station->imageUrl();
    const QString button0Url = m_station->streamUrl();

    activity["type"] = Discord::LISTENING;
    activity["timestamps"] = QJsonObject {
        {"start", m_startedListeningAt}
    };
    activity["status_display_type"]
        = (details.isEmpty()) ? Discord::NAME : Discord::DETAILS;

    if (details.isEmpty())
    {
        details = tr("Unnamed Station");
    }
    else
    {
        if (details.size() == 1)
        {
            details += "​";
        }
        else if (details.size() > 128)
        {
            details = details.first(64) + "…" + details.last(63);
        }
    }

    activity["details"] = details;

    if (!state.isEmpty())
    {
        const QString stateUrl
            = QUrl(QString("https://google.com/search?q=site:shazam.com %0")
                       .arg(QUrl::toPercentEncoding(state)))
                  .toString(QUrl::FullyEncoded);

        if (state.size() == 1)
        {
            state += "​";
        }
        else if (state.size() > 128)
        {
            state = state.first(64) + "…" + state.last(63);
        }

        activity["state"] = state;

        if (stateUrl.size() <= 256)
        {
            activity["state_url"] = stateUrl;
        }
    }

    if (!QUrl(largeImage).isValid() || largeImage.size() > 300)
    {
        largeImage = "https://raw.githubusercontent.com/Zet0x0/Radio/refs/"
                     "heads/master/src/icons/discord/large-image.png";
    }

    activity["assets"] = QJsonObject {
        {"large_image", largeImage                       },
        {"small_image",
         "https://raw.githubusercontent.com/Zet0x0/Radio/refs/heads/master/src/"
         "icons/discord/small-image.png"                 },
        { "small_text",                       tr("Radio")},
        {  "small_url", "https://github.com/Zet0x0/Radio"},
    };

    if (button0Url.size() <= 512)
    {
        activity["buttons"]
            = QJsonArray {{QJsonObject {{"label", "Tune In (Browser)"},
                                        {"url", button0Url}}}};
    }

    Discord::setActivity(activity);
}
