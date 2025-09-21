#include "player.h"

#include "../dialogcontroller.h"
#include "../discord.h"
#include "../settings.h"
#include "../utilities.h"
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
    newNowPlaying = Utilities::escapeControlCharacters(newNowPlaying);

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

quint16 Player::volume() const
{
    return m_volume;
}

void Player::setVolume(const quint16 &newVolume)
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
    if (m_station->isInvalid())
    {
        return;
    }

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

    Settings *settings = Settings::instance();

    setVolume(settings->audioVolume());
    setMuted(settings->audioMuted());
    setStation(settings->privateSavedCurrentStation());

    if (settings->playbackAutoPlayOnStart()
        || (settings->playbackResumeOnStart()
            && settings->privateLastSavedPlayerState() != Player::STOPPED))
    {
        play();
    }

    setInitialized(true);

    qCInfo(radioPlayer) << "initialized";
}

bool Player::initialized() const
{
    return m_initialized;
}

void Player::updateDiscordActivity()
{
    m_discordActivityTimer->stop();

    if (m_state != PLAYING)
    {
        Discord::clearActivity();
    }
    else
    {
        QJsonObject activity;

        QString details = m_station->name();
        QString state = m_nowPlaying;
        QString largeImage = m_station->imageUrl();
        const QString button0Url = m_station->streamUrl();

        activity["type"] = Discord::LISTENING;
        activity["timestamps"] = QJsonObject{
            { "start", m_startedListeningAt }
        };

        switch (Settings::instance()->discordPrioritizedStatusDisplayType())
        {
            case Discord::STATE:
            {
                activity["status_display_type"]
                    = (!state.isEmpty())
                        ? Discord::STATE
                        : ((!details.isEmpty()) ? Discord::DETAILS
                                                : Discord::NAME);

                break;
            }

            case Discord::DETAILS:
            {
                activity["status_display_type"]
                    = (!details.isEmpty()) ? Discord::DETAILS : Discord::NAME;

                break;
            }

            case Discord::NAME:
            default:
            {
                activity["status_display_type"] = Discord::NAME;

                break;
            }
        }

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
            const QString stateUrl = Utilities::getShazamLinkFor(state);

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

        if (largeImage.isEmpty() || largeImage.size() > 300)
        {
            largeImage = "https://raw.githubusercontent.com/Zet0x0/Radio/refs/"
                         "heads/master/src/icons/discord/large-image.png";
        }

        activity["assets"] = QJsonObject{
            { "large_image", largeImage                        },
            { "small_image",
             "https://raw.githubusercontent.com/Zet0x0/Radio/refs/heads/"
              "master/"
              "src/icons/discord/small-image.gif"              },
            { "small_text",  tr("Radio")                       },
            { "small_url",   "https://github.com/Zet0x0/Radio" },
        };

        if (QUrl(button0Url).isValid() && button0Url.size() <= 512)
        {
            activity["buttons"] = QJsonArray{ { QJsonObject{
                { "label", tr("Tune In (Browser)") },
                { "url", button0Url } } } };
        }

        Discord::setActivity(activity);
    }

    m_discordActivityTimer->start();
}

Player::Player()
{
    Settings *settings = Settings::instance();

    connect(this,
            &Player::stateChanged,
            this,
            [this, settings]
            {
                switch (m_state)
                {
                    case PLAYING:
                    {
                        m_startedListeningAt
                            = QDateTime::currentSecsSinceEpoch();

                        if (settings->discordEnabled())
                        {
                            updateDiscordActivity();
                        }

                        break;
                    }
                    default:
                    {
                        m_discordActivityTimer->stop();
                        Discord::clearActivity();

                        m_startedListeningAt = -1;

                        break;
                    }
                }
            });
    connect(this,
            &Player::nowPlayingChanged,
            this,
            &Player::updateDiscordActivity);
    connect(this,
            &Player::nowPlayingChanged,
            this,
            [this]
            {
                m_mpv->setProperty("title",
                                   (m_nowPlaying.isEmpty())
                                       ? tr("Radio")
                                       : tr("%0 - Radio").arg(m_nowPlaying));
            });
    connect(this,
            &Player::mutedChanged,
            settings,
            [settings, this]
            {
                settings->setAudioMuted(m_muted);
            });
    connect(this,
            &Player::volumeChanged,
            settings,
            [settings, this]
            {
                settings->setAudioVolume(m_volume);
            });
    connect(this,
            &Player::stationChanged,
            settings,
            [settings, this]
            {
                settings->setPrivateSavedCurrentStation(m_station);
            });
    connect(this,
            &Player::stateChanged,
            settings,
            [settings, this]
            {
                settings->setPrivateLastSavedPlayerState(m_state);
            });

    connect(m_discordActivityTimer,
            &QTimer::timeout,
            this,
            &Player::updateDiscordActivity);
    connect(settings,
            &Settings::discordPrioritizedStatusDisplayTypeChanged,
            this,
            &Player::updateDiscordActivity);
    connect(settings,
            &Settings::discordActivityUpdateIntervalChanged,
            m_discordActivityTimer,
            [this, settings]
            {
                m_discordActivityTimer->setInterval(
                    settings->discordActivityUpdateInterval());
            });
    m_discordActivityTimer->setInterval(
        settings->discordActivityUpdateInterval());
    m_discordActivityTimer->setSingleShot(true);
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

