#include "mpveventmanager.h"

#include "mpv.h"

Q_LOGGING_CATEGORY(radioMpvEventManager, "radio.mpv.eventManager")

MpvEventManager *MpvEventManager::instance()
{
    static MpvEventManager *instance = new MpvEventManager;

    return instance;
}

void MpvEventManager::listenToEvents()
{
    mpv_handle *mpvHandle = Mpv::mpvHandle();

    while (true)
    {
        handleEvent(mpv_wait_event(mpvHandle, -1));
    }
}

void MpvEventManager::handleEvent(mpv_event *event)
{
    const mpv_event_id eventId = event->event_id;
    void *eventData = event->data;

    switch (eventId)
    {
        case MPV_EVENT_START_FILE:
        {
            emit playerStateChanged(Player::LOADING);

            break;
        }
        case MPV_EVENT_FILE_LOADED:
        {
            emit playerStateChanged(Player::PLAYING);

            break;
        }
        case MPV_EVENT_END_FILE:
        {
            emit playerStateChanged(Player::STOPPED);

            mpv_event_end_file *endFile
                = static_cast<mpv_event_end_file *>(eventData);

            switch (endFile->reason)
            {
                case MPV_END_FILE_REASON_ERROR:
                {
                    emit playbackErrorOccurred(endFile->error);

                    break;
                }

                case MPV_END_FILE_REASON_EOF:
                {
                    emit playbackErrorOccurred(MPV_ERROR_LOADING_FAILED);

                    break;
                }

                default:
                {
                    break;
                }
            }

            break;
        }

        case MPV_EVENT_PROPERTY_CHANGE:
        {
            mpv_event_property *property
                = static_cast<mpv_event_property *>(eventData);

            const QString propertyName = property->name;
            const mpv_format propertyFormat = property->format;
            void *propertyData = property->data;

            if (propertyName == "media-title") /* now playing */
            {
                emit nowPlayingChanged(
                    (propertyFormat == MPV_FORMAT_NONE)
                        ? QString()
                        : QString(*static_cast<char **>(propertyData))
                              .trimmed());
            }
            else if (propertyName == "time-pos") /* elapsed */
            {
                emit elapsedChanged((propertyFormat == MPV_FORMAT_NONE)
                                        ? 0
                                        : *static_cast<qint64 *>(propertyData));
            }
            else
            {
                qCWarning(radioMpvEventManager)
                    << "property" << propertyName
                    << "change not normally expected, so not handled";
            }

            break;
        }

        case MPV_EVENT_LOG_MESSAGE:
        {
            const mpv_event_log_message *logMessage_
                = static_cast<mpv_event_log_message *>(eventData);

            emit logMessage(logMessage_->log_level,
                            logMessage_->prefix,
                            logMessage_->text);

            break;
        }

        /*
         * events that don't require much handling other than a simple
         * log message
         */
        case MPV_EVENT_IDLE:
        {
            qCInfo(radioMpv) << "instance entered idle mode";

            break;
        }
        case MPV_EVENT_AUDIO_RECONFIG:
        {
            qCInfo(radioMpv) << "audio reconfigured";

            break;
        }
        case MPV_EVENT_PLAYBACK_RESTART:
        {
            qCInfo(radioMpv) << "playback reinitialized";

            break;
        }

        default:
        {
            qCWarning(radioMpvEventManager)
                << "event with id" << eventId << '(' << mpv_event_name(eventId)
                << ')' << "not normally expected, so not handled";

            break;
        }
    }
}
