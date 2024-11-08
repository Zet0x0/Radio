#include "player.h"
#include "discord.h"
#include "nowPlayingImageProvider.h"
#include "streamUrlParser.h"
#include "utilities.h"
#include <QCoreApplication>
#include <QJsonArray>
#include <QtConcurrentRun>

Q_LOGGING_CATEGORY(radio_player, "radio.player")
Q_LOGGING_CATEGORY(radio_player_libVlc, "radio.player.libVlc")

Player::Player()
{
    connect(this, &Player::libVlcInitialized, this, &Player::initialize);
}

Player *Player::instance()
{
    static Player *instance = new Player;

    return instance;
}

Player *Player::qmlInstance(QQmlEngine *, QJSEngine *)
{
    return instance();
}

bool Player::setEqualizer(libvlc_equalizer_t *equalizer)
{
    return libvlc_media_player_set_equalizer(instance()->m_mediaPlayer, equalizer) > -1;
}

bool Player::isMuted()
{
    return libvlc_audio_get_mute(m_mediaPlayer);
}

QString Player::getCurrentStreamUrl()
{
    libvlc_media_list_lock(m_mediaList);

    libvlc_media_t *currentMedia =
        libvlc_media_list_item_at_index(m_mediaList, libvlc_media_list_count(m_mediaList) - 1);

    libvlc_media_list_unlock(m_mediaList);

    const QStringList streamUrls = m_station.streamUrls;
    const QString streamUrl =
        (currentMedia) ? libvlc_media_get_meta(currentMedia, libvlc_meta_URL)
                       : ((streamUrls.isEmpty()) ? QString() : streamUrls.at(m_streamUrlIndex));

    libvlc_media_release(currentMedia);

    return streamUrl;
}

const QStringList Player::libVlcLogMessages()
{
    return instance()->m_libVlcLogMessages;
}

void Player::beginInitialization()
{
    if (m_initialized)
    {
        return;
    }

    setInitializationState("Beginning initialization...");

    initializeLibVlc();
}

void Player::setStation(const Station &station)
{
    if (station == m_station)
    {
        return;
    }

    stop();

    m_station = station;

    removeMediaFromMediaList();

    m_allStreamUrlsFailed = false;

    setStreamUrlIndex(0);

    qCDebug(radio_player) << "new value for station:" << station;

    emit stationChanged(station);
}

void Player::setVolume(const int &volume)
{
    if (volume == m_volume)
    {
        return;
    }

    qCDebug(radio_player).nospace() << "setting volume to: " << volume << '%';

    const bool setVolumeSucceeded = libvlc_audio_set_volume(m_mediaPlayer, volume) == 0;

    emit volumeChanged((setVolumeSucceeded) ? volume : m_volume);

    if (setVolumeSucceeded)
    {
        m_volume = volume;
    }
}

void Player::setMuted(const bool &muted)
{
    if (muted == isMuted())
    {
        return;
    }

    libvlc_audio_set_mute(m_mediaPlayer, muted);

    qCDebug(radio_player) << "new value for muted:" << muted;

    emit mutedChanged(muted);
}

void Player::play()
{
    const QStringList streamUrls = m_station.streamUrls;

    if (streamUrls.isEmpty())
    {
        reportError("Playback Error", "Station's list of Stream URLs is empty.");

        return;
    }

    const QString currentStreamUrl = streamUrls.at(m_streamUrlIndex);

    if (!StreamUrlParser::shouldParse(currentStreamUrl))
    {
        play(currentStreamUrl);

        return;
    }

    setState(ParsingStreamUrlState);

    StreamUrlParser::beginParsing(currentStreamUrl);
}

void Player::stop()
{
    if (m_state == ParsingStreamUrlState)
    {
        StreamUrlParser::abortPendingParsing();

        setState(StoppedState);

        return;
    }

    qCDebug(radio_player) << "requesting media stop";

    emit mediaStopRequested();

    libvlc_media_player_stop(m_mediaPlayer);
}

void Player::initializeLibVlc()
{
    setInitializationState("Initializing LibVLC...");

    const QFuture<void> future = QtConcurrent::run(
        [this]
        {
            setInitializationDetails("Initializing the LibVLC instance...");

            libvlc_instance_t *libVlcInstance = m_libVlcInstance = libvlc_new(0, NULL);

            if (!libVlcInstance)
            {
                setInitializationError(
                    "Failed to initialize the LibVLC instance.",
                    "Either the command line options were invalid or no plugins were found.");

                return;
            }

            setInitializationDetails("Setting up our own logging function for LibVLC...");

            libvlc_log_set(
                libVlcInstance,
                [](void *, int level, const libvlc_log_t *ctx, const char *fmt, va_list args)
                {
                    Player *instance = Player::instance();

                    const char *moduleName;
                    const char *objectName;

                    libvlc_log_get_context(ctx, &moduleName, NULL, NULL);
                    libvlc_log_get_object(ctx, &objectName, NULL, NULL);

                    QString rawLibVlcLogMessage =
                        QString("%0 %1 %2: %3")
                            .arg(moduleName, objectName, "%0", QString::vasprintf(fmt, args));

                    switch (level)
                    {
                        case LIBVLC_DEBUG:
                        {
                            rawLibVlcLogMessage = rawLibVlcLogMessage.arg("debug");

                            qCDebug(radio_player_libVlc).noquote() << rawLibVlcLogMessage;

                            break;
                        }

                        case LIBVLC_NOTICE:
                        {
                            rawLibVlcLogMessage = rawLibVlcLogMessage.arg("notice");

                            qCInfo(radio_player_libVlc).noquote() << rawLibVlcLogMessage;

                            break;
                        }

                        case LIBVLC_WARNING:
                        {
                            rawLibVlcLogMessage = rawLibVlcLogMessage.arg("warning");

                            qCWarning(radio_player_libVlc).noquote() << rawLibVlcLogMessage;

                            break;
                        }

                        case LIBVLC_ERROR:
                        {
                            rawLibVlcLogMessage = rawLibVlcLogMessage.arg("error");

                            qCCritical(radio_player_libVlc).noquote() << rawLibVlcLogMessage;

                            break;
                        }

                        default:
                        {
                            rawLibVlcLogMessage = rawLibVlcLogMessage.arg("[[unknown level]]");

                            qCWarning(radio_player_libVlc).noquote()
                                << "message with undefined level:" << rawLibVlcLogMessage;

                            break;
                        }
                    }

                    const QString formattedLibVlcLogMessage = QString("%0 | %1").arg(
                        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz"),
                        rawLibVlcLogMessage);

                    instance->m_libVlcLogMessages << formattedLibVlcLogMessage;

                    emit instance->newLibVlcLogMessage(formattedLibVlcLogMessage);
                },
                NULL);

            setInitializationDetails("Initializing media player...");

            libvlc_media_player_t *mediaPlayer = m_mediaPlayer =
                libvlc_media_player_new(libVlcInstance);

            if (!mediaPlayer)
            {
                setInitializationError("Failed to initialize media player.");

                return;
            }

            setInitializationDetails("Initializing media list player...");

            libvlc_media_list_player_t *mediaListPlayer = m_mediaListPlayer =
                libvlc_media_list_player_new(libVlcInstance);

            if (!mediaListPlayer)
            {
                setInitializationError("Failed to initialize media list player.");

                return;
            }

            setInitializationDetails("Initializing media list...");

            libvlc_media_list_t *mediaList = m_mediaList = libvlc_media_list_new(libVlcInstance);

            if (!mediaList)
            {
                setInitializationError("Failed to initialize media list.");

                return;
            }

            libvlc_event_manager_t *mediaPlayerEventManager =
                libvlc_media_player_event_manager(mediaPlayer);

            const QList<libvlc_event_e> mediaPlayerEventList{
                /*libvlc_MediaPlayerOpening,        */ libvlc_MediaPlayerBuffering, /*
                libvlc_MediaPlayerPlaying,          libvlc_MediaPlayerPaused,
                libvlc_MediaPlayerStopped,          libvlc_MediaPlayerEndReached,
                libvlc_MediaPlayerEncounteredError, */
                libvlc_MediaPlayerTimeChanged};

            for (const libvlc_event_e &event : mediaPlayerEventList)
            {
                const QString stringifiedEvent = libvlc_event_type_name(event);

                setInitializationDetails(
                    QString("Attaching event %0 to the event handler...").arg(stringifiedEvent));

                if (libvlc_event_attach(mediaPlayerEventManager, event, libVlcEventHandler, NULL) !=
                    ENOMEM)
                {
                    continue;
                }

                setInitializationError(QString("Failed to attach event %0 to the event handler.")
                                           .arg(stringifiedEvent),
                                       "Cannot allocate memory.");

                return;
            }

            libvlc_media_list_player_set_media_player(mediaListPlayer, mediaPlayer);
            libvlc_media_list_player_set_media_list(mediaListPlayer, mediaList);

            setInitializationDetails("Finished.");

            emit libVlcInitialized(QPrivateSignal());
        });
}

void Player::initialize()
{
    setInitializationState("Initializing Player...");
    resetInitializationDetails();

    setInitializationDetails("Connecting Stream URL Parser signals...");

    StreamUrlParser *streamUrlParser = StreamUrlParser::instance();

    connect(streamUrlParser, &StreamUrlParser::zenoFmSiteBuildIdRefreshingErrorOccurred, this,
            [this](const QString &streamUrl, const QString &errorString)
            {
                setState(ErrorState);

                emit streamUrlErrorOccurred(
                    QString("The Stream URL Parser failed to retrieve Zeno.FM's site buildId "
                            "required for Stream URL %0 parsing.")
                        .arg(streamUrl),
                    errorString, QPrivateSignal());
            });
    connect(streamUrlParser, &StreamUrlParser::streamUrlParsingErrorOccurred, this,
            [this](const QString &streamUrl, const QString &errorString)
            {
                qCWarning(radio_player).nospace()
                    << "failed to parse stream url " << streamUrl << ": " << errorString;

                emit streamUrlErrorOccurred(
                    QString("Failed to parse Stream URL %0.").arg(streamUrl), errorString,
                    QPrivateSignal());
            });
    connect(streamUrlParser, &StreamUrlParser::streamUrlParsingFinished, this,
            [this](const QString &parsedStreamUrl)
            {
                qCDebug(radio_player) << "requesting to play parsed stream url:" << parsedStreamUrl;

                play(parsedStreamUrl);
            });

    setInitializationDetails("Connecting Now Playing Image Provider signals...");

    connect(NowPlayingImageProvider::instance(), &NowPlayingImageProvider::currentImageUrlChanged,
            this, &Player::updateDiscordActivity);

    setInitializationDetails("Connecting Player signals...");

    connect(this, &Player::streamUrlErrorOccurred, this,
            [this](const QString &errorString, const QString &details)
            {
                if (m_streamUrlIndex < m_station.streamUrls.size() - 1)
                {
                    qCWarning(radio_player).nospace()
                        << "could not play media at index " << m_streamUrlIndex
                        << ", trying next stream url (error string: " << errorString << ')';

                    setStreamUrlIndex(m_streamUrlIndex + 1);

                    play();

                    return;
                }

                qCCritical(radio_player)
                    << "every stream url failed to play, giving up and letting it go";

                m_allStreamUrlsFailed = true;

                setState(ErrorState);

                reportError("Stream URL Error", errorString, details);
            });
    connect(this, &Player::stateChanged, this,
            [this](const State &state)
            {
                const bool loading = state == ParsingStreamUrlState || state == OpeningState ||
                                     state == BufferingState;

                setPlaying(loading || state == PlayingState);
                setLoading(loading);
            });
    connect(this, &Player::playingChanged, this,
            [this](const bool &playing)
            {
                if (playing)
                {
                    return;
                }

                m_startedListeningAt = 0;
                setNowPlaying(QString());
                setElapsed(0);
            });
    connect(this, &Player::elapsedChanged, this,
            [this](const int &elapsed)
            {
                if (elapsed > 0)
                {
                    return;
                }

                m_startedListeningAt = QDateTime::currentMSecsSinceEpoch();

                updateDiscordActivity();
            });

    connect(this, &Player::stationChanged, this, &Player::updateDiscordActivity);
    connect(this, &Player::nowPlayingChanged, this, &Player::updateDiscordActivity);
    connect(this, &Player::playingChanged, this, &Player::updateDiscordActivity);

    m_station.title = "No station selected.";

    resetInitializationState();
    resetInitializationDetails();

    setInitialized(true);
}

void Player::setInitialized(const bool &initialized)
{
    if (initialized == m_initialized)
    {
        return;
    }

    m_initialized = initialized;

    qCDebug(radio_player) << "new value for initialized:" << initialized;

    emit initializedChanged(initialized);
}

void Player::setInitializationError(const QString &message, const QString &details)
{
    setInitializationState(message);
    setInitializationDetails(getLibVlcErrorMessage(details));
    setInitializationFailed(true);
}

void Player::setInitializationFailed(const bool &initializationFailed)
{
    if (initializationFailed == m_initializationFailed)
    {
        return;
    }

    m_initializationFailed = initializationFailed;

    qCDebug(radio_player) << "new value for initializationFailed:" << initializationFailed;

    emit initializationFailedChanged(initializationFailed);
}

void Player::setInitializationState(const QString &initializationState)
{
    if (initializationState == m_initializationState)
    {
        return;
    }

    m_initializationState = initializationState;

    qCDebug(radio_player) << "new value for initializationState:" << initializationState;

    emit initializationStateChanged(initializationState);
}

void Player::resetInitializationState()
{
    setInitializationState(QString());
}

void Player::setInitializationDetails(const QString &initializationDetails)
{
    if (initializationDetails == m_initializationDetails)
    {
        return;
    }

    m_initializationDetails = initializationDetails;

    qCDebug(radio_player) << "new value for initializationDetails:" << initializationDetails;

    emit initializationDetailsChanged(initializationDetails);
}

void Player::resetInitializationDetails()
{
    setInitializationDetails(QString());
}

void Player::reportError(const QString &title, const QString &message, const QString &details)
{
    qCCritical(radio_player).nospace()
        << "error, title: " << title << ", message: " << message << ", details: " << details;

    Utilities::requestMessageDialog(title, message, details);
}

void Player::setNowPlaying(QString nowPlaying)
{
    nowPlaying = Utilities::sanitizeString(nowPlaying);

    if (nowPlaying == m_nowPlaying)
    {
        return;
    }

    m_nowPlaying = nowPlaying;

    qCDebug(radio_player) << "new value for nowPlaying:" << nowPlaying;

    emit nowPlayingChanged(nowPlaying);
}

void Player::setElapsed(const int &elapsed)
{
    if (elapsed == m_elapsed)
    {
        return;
    }

    m_elapsed = elapsed;

    emit elapsedChanged(elapsed);
}

void Player::setState(const State &state)
{
    if (state == m_state)
    {
        return;
    }

    m_state = state;

    qCDebug(radio_player) << "new value for state:" << state;

    emit stateChanged(state);
}

void Player::setPlaying(const bool &playing)
{
    if (playing == m_playing)
    {
        return;
    }

    m_playing = playing;

    qCDebug(radio_player) << "new value for playing:" << playing;

    emit playingChanged(playing);
}

void Player::setLoading(const bool &loading)
{
    if (loading == m_loading)
    {
        return;
    }

    m_loading = loading;

    qCDebug(radio_player) << "new value for loading:" << loading;

    emit loadingChanged(loading);
}

void Player::setBufferProgress(const int &bufferProgress)
{
    if (bufferProgress == m_bufferProgress)
    {
        return;
    }

    m_bufferProgress = bufferProgress;

    qCDebug(radio_player) << "new value for bufferProgress:" << bufferProgress;

    emit bufferProgressChanged(bufferProgress);
}

void Player::setStreamUrlIndex(const int &streamUrlIndex)
{
    if (streamUrlIndex == m_streamUrlIndex)
    {
        return;
    }

    m_streamUrlIndex = streamUrlIndex;

    qCDebug(radio_player) << "new value for streamUrlIndex:" << streamUrlIndex;

    emit streamUrlIndexChanged(streamUrlIndex);
}

void Player::play(const QString &streamUrl)
{
    qCDebug(radio_player) << "attempting to play stream url" << streamUrl;

    removeMediaFromMediaList();

    if (m_allStreamUrlsFailed)
    {
        m_allStreamUrlsFailed = false;

        setStreamUrlIndex(0);
    }

    libvlc_media_t *media = libvlc_media_new_location(m_libVlcInstance, streamUrl.toUtf8());

    if (!media)
    {
        reportError("Media Initialization Error", "Failed to initialize media.",
                    getLibVlcErrorMessage());

        return;
    }

    qCDebug(radio_player) << "attaching event \"MediaMetaChanged\" to the event handler";

    if (libvlc_event_attach(libvlc_media_event_manager(media), libvlc_MediaMetaChanged,
                            libVlcEventHandler, NULL) == ENOMEM)
    {
        qCWarning(radio_player) << "failed to attach event \"MediaMetaChanged\" to the event "
                                   "handler: \"Cannot allocate memory.\"";
    }
    libvlc_event_attach(libvlc_media_event_manager(media), libvlc_MediaStateChanged,
                        libVlcEventHandler, NULL);

    libvlc_media_set_meta(media, libvlc_meta_URL, streamUrl.toUtf8());

    libvlc_media_list_lock(m_mediaList);

    const bool mediaListAddMediaSucceeded = libvlc_media_list_add_media(m_mediaList, media) == 0;

    if (!mediaListAddMediaSucceeded)
    {
        reportError("Media List Error", "Failed to add media to media list.",
                    getLibVlcErrorMessage());
    }

    libvlc_media_list_unlock(m_mediaList);

    if (mediaListAddMediaSucceeded &&
        libvlc_media_list_player_play_item(m_mediaListPlayer, media) < 0)
    {
        reportError("Media List Player Error", "Failed to play media.", getLibVlcErrorMessage());
    }

    libvlc_media_release(media);
}

void Player::removeMediaFromMediaList()
{
    libvlc_media_list_lock(m_mediaList);

    const int mediaListItemCount = libvlc_media_list_count(m_mediaList);

    for (int i = 0; i < mediaListItemCount; ++i)
    {
        qCDebug(radio_player) << "removing first media from the media list" << i;

        if (libvlc_media_list_remove_index(m_mediaList, 0) > -1)
        {
            continue;
        }

        const QString libVlcErrorMessage = getLibVlcErrorMessage();

        qCWarning(radio_player).nospace().noquote()
            << "failed to remove first media from the media list (" << i << ')'
            << ((libVlcErrorMessage.isEmpty()) ? QString()
                                               : QString(": \"%0\"").arg(libVlcErrorMessage));
    }

    libvlc_media_list_unlock(m_mediaList);
}

QString Player::getLibVlcErrorMessage(const QString &defaultValue)
{
    const QString libVlcErrorMessage = libvlc_errmsg();

    return (libVlcErrorMessage.isEmpty()) ? defaultValue : libVlcErrorMessage;
}

void Player::libVlcEventHandler(const libvlc_event_t *event, void *)
{
    Player *instance = Player::instance();

    const int eventType = event->type;

    switch (eventType)
    {
        case libvlc_MediaMetaChanged:
        {
            if (event->u.media_meta_changed.meta_type != libvlc_meta_NowPlaying)
            {
                break;
            }

            const QString nowPlaying =
                QString(libvlc_media_get_meta(static_cast<libvlc_media_t *>(event->p_obj),
                                              libvlc_meta_NowPlaying))
                    .trimmed();

            instance->setNowPlaying((nowPlaying == instance->m_station.title) ? QString()
                                                                              : nowPlaying);

            break;
        }

        case libvlc_MediaPlayerTimeChanged:
        {
            instance->setElapsed(event->u.media_player_time_changed.new_time / 1000);

            break;
        }

        case libvlc_MediaStateChanged:
        {
            const int state = event->u.media_state_changed.new_state;

            switch (state)
            {
                case libvlc_Opening:
                {
                    instance->setState(OpeningState);

                    break;
                }
                case libvlc_Buffering:
                {
                    instance->setBufferProgress(event->u.media_player_buffering.new_cache);

                    instance->setState(BufferingState);

                    break;
                }
                case libvlc_Playing:
                {
                    instance->setState(PlayingState);

                    break;
                }
                case libvlc_Paused:
                {
                    instance->setState(PausedState);

                    break;
                }
                case libvlc_Stopped:
                {
                    instance->setState(StoppedState);

                    break;
                }
                case libvlc_Ended:
                {
                    instance->setState(EndedState);

                    break;
                }
                case libvlc_Error:
                {
                    instance->setState(ErrorState);

                    emit instance->streamUrlErrorOccurred("Media player encountered an error.",
                                                          instance->getLibVlcErrorMessage(),
                                                          QPrivateSignal());

                    break;
                }
            }

            break;
        }

        case libvlc_MediaPlayerOpening:
        {
            instance->setState(OpeningState);

            break;
        }
        case libvlc_MediaPlayerBuffering:
        {
            instance->setBufferProgress(event->u.media_player_buffering.new_cache);

            instance->setState(BufferingState);

            break;
        }
        case libvlc_MediaPlayerPlaying:
        {
            instance->setState(PlayingState);

            break;
        }
        case libvlc_MediaPlayerPaused:
        {
            instance->setState(PausedState);

            break;
        }
        case libvlc_MediaPlayerStopped:
        {
            instance->setState(StoppedState);

            break;
        }
        case libvlc_MediaPlayerEndReached:
        {
            instance->setState(EndedState);

            break;
        }
        case libvlc_MediaPlayerEncounteredError:
        {
            instance->setState(ErrorState);

            emit instance->streamUrlErrorOccurred("Media player encountered an error.",
                                                  instance->getLibVlcErrorMessage(),
                                                  QPrivateSignal());

            break;
        }

        default:
        {
            qCWarning(radio_player)
                << "unhandled libvlc event:" << libvlc_event_type_name(eventType);

            break;
        }
    }
}

void Player::updateDiscordActivity()
{
    qCDebug(radio_player) << "updating discord activity";

    QJsonObject activity;

    if (m_playing)
    {
        QString largeImage;
        const QStringList largeImageUrls = {NowPlayingImageProvider::currentImageUrl(),
                                            m_station.imageUrl, "applicationicon"};

        for (const QString &largeImageUrl : largeImageUrls)
        {
            if (largeImage.isEmpty() || largeImage.size() >= 512 || !QUrl(largeImage).isValid())
            {
                largeImage = largeImageUrl;
            }
        }

        activity = {
            {"type",       Discord::ActivityType::Listening        },
            {"created_at", m_startedListeningAt                    },
            {"assets",     QJsonObject{{"large_image", largeImage}}}
        };

        const QString largeText = m_station.subtitle;
        const QString state = m_station.title;
        const QString streamUrl = getCurrentStreamUrl();

        if (!largeText.isEmpty())
        {
            QJsonObject assets = activity["assets"].toObject();
            assets["large_text"] = (largeText.size() > 128) ? (largeText.first(127) + "…")
                                                            : largeText.leftJustified(2);

            activity["assets"] = assets;
        }

        if (!state.isEmpty())
        {
            activity["state"] =
                (state.size() > 128) ? (state.first(127) + "…") : state.leftJustified(2);
        }

        if (!m_nowPlaying.isEmpty())
        {
            activity["details"] = (m_nowPlaying.size() > 128) ? (m_nowPlaying.first(127) + "…")
                                                              : m_nowPlaying.leftJustified(2);
        }

        if (!streamUrl.isEmpty() && streamUrl.size() <= 512)
        {
            const QUrl qUrl_streamUrl = QUrl(streamUrl);

            if (!qUrl_streamUrl.scheme().isEmpty() && qUrl_streamUrl.isValid())
            {
                activity["buttons"] = QJsonArray{
                    QJsonObject{{"label", "Tune In (Browser)"}, {"url", streamUrl}},
                    QJsonObject{{"label", "Tune In (App)"},
                                {"url", "radio://tune-in?url=" + streamUrl}       }
                };
            }
        }
    }

    Discord::setActivity((activity.isEmpty()) ? QJsonValue() : QJsonValue(activity));
}
