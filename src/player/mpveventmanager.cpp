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

    qCInfo(radioMpvEventManager) << "started listening to events";

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
            emit playerStateChanged(Player::State::LOADING);

            break;
        }
        case MPV_EVENT_FILE_LOADED:
        {
            emit playerStateChanged(Player::State::PLAYING);

            break;
        }
        case MPV_EVENT_END_FILE:
        {
            mpv_event_end_file *endFile = static_cast<mpv_event_end_file *>(eventData);
            const mpv_end_file_reason endFileReason = endFile->reason;

            switch (endFileReason)
            {
                case MPV_END_FILE_REASON_ERROR:
                case MPV_END_FILE_REASON_EOF:
                {
                    emit errorOccurred((endFileReason == MPV_END_FILE_REASON_ERROR)
                                           ? endFile->error
                                           : MPV_ERROR_NOTHING_TO_PLAY);

                    break;
                }

                default:
                {
                    break;
                }
            }

            emit playerStateChanged(Player::State::STOPPED);

            break;
        }

        case MPV_EVENT_PROPERTY_CHANGE:
        {
            mpv_event_property *property = static_cast<mpv_event_property *>(eventData);

            const QString propertyName = property->name;
            const mpv_format propertyFormat = property->format;
            void *propertyData = property->data;

            if (propertyName == "metadata/by-key/icy-title") // now playing
            {
                emit nowPlayingChanged((propertyFormat == MPV_FORMAT_NONE)
                                           ? QString()
                                           : *static_cast<char **>(propertyData));
            }
            else if (propertyName == "time-pos") // elapsed
            {
                emit elapsedChanged((propertyFormat == MPV_FORMAT_NONE)
                                        ? 0
                                        : *static_cast<qint64 *>(propertyData));
            }
            else if (propertyName == "volume") // volume
            {
                emit volumeChanged((propertyFormat == MPV_FORMAT_NONE)
                                       ? 100.0
                                       : *static_cast<qreal *>(propertyData));
            }
            else if (propertyName == "mute") // muted
            {
                emit mutedChanged((propertyFormat == MPV_FORMAT_NONE)
                                      ? false
                                      : QString(*static_cast<char **>(propertyData)) == "yes");
            }
            else
            {
                qCWarning(radioMpvEventManager) << "property" << propertyName << "change not normally expected, so not handled";
            }

            break;
        }

        case MPV_EVENT_LOG_MESSAGE:
        {
            emit logMessage(static_cast<mpv_event_log_message *>(eventData));

            break;
        }

        default:
        {
            qCWarning(radioMpvEventManager) << "event with id" << eventId << "(" << mpv_event_name(eventId) << ")"
                                            << "not normally expected, so not handled";

            break;
        }
    }
}
