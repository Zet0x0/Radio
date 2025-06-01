#include "mpv.h"

#include "../utilities.h"
#include "mpveventmanager.h"

#include <QVariant>

// a class function wouldn't work to get rid of this macro
#define printMpvLogMessage(debug, logMessage) debug.noquote() << logMessage->prefix << QString(logMessage->text).trimmed()

Q_LOGGING_CATEGORY(radioMpv, "radio.mpv")
Q_LOGGING_CATEGORY(mpv, "mpv")

Mpv *Mpv::instance()
{
    static Mpv *instance = new Mpv;

    return instance;
}

bool Mpv::play(const QString &url)
{
    const char *args[] = {"loadfile", Utilities::toCString(url), NULL};

    return !handleError(command(args));
}

bool Mpv::stop()
{
    const char *args[] = {"stop", NULL};

    return !handleError(command(args));
}

bool Mpv::setVolume(const qreal &volume)
{
    return setProperty("volume", MPV_FORMAT_DOUBLE, volume) >= 0;
}

bool Mpv::setMuted(const bool &muted)
{
    return setProperty("mute", MPV_FORMAT_STRING, (muted) ? "yes" : "no") >= 0;
}

mpv_handle *Mpv::mpvHandle()
{
    return instance()->m_mpvHandle;
}

// TODO: implement this properly, ui-wise too
bool Mpv::handleError(const int &errorCode)
{
    if (errorCode == MPV_ERROR_SUCCESS)
    {
        return false;
    }

    qDebug() << mpv_error_string(errorCode);

    return true;
}

void Mpv::handleLogMessage(mpv_event_log_message *logMessage)
{
    switch (logMessage->log_level)
    {
        case MPV_LOG_LEVEL_FATAL:
        {
            printMpvLogMessage(qCFatal(mpv), logMessage);

            break;
        }
        case MPV_LOG_LEVEL_ERROR:
        {
            printMpvLogMessage(qCCritical(mpv), logMessage);

            break;
        }
        case MPV_LOG_LEVEL_WARN:
        {
            printMpvLogMessage(qCWarning(mpv), logMessage);

            break;
        }
        case MPV_LOG_LEVEL_DEBUG:
        {
            printMpvLogMessage(qCDebug(mpv), logMessage);

            break;
        }
        case MPV_LOG_LEVEL_INFO:
        case MPV_LOG_LEVEL_V:
        case MPV_LOG_LEVEL_TRACE:
        default:
        {
            printMpvLogMessage(qCInfo(mpv), logMessage);

            break;
        }
    }
}

Mpv::Mpv()
{
    if (handleError(create()))
    {
        return;
    }

    requestLogMessages();

    MpvEventManager *eventManager = MpvEventManager::instance();

    connect(eventManager, &MpvEventManager::errorOccurred, this, &Mpv::handleError);
    connect(eventManager, &MpvEventManager::logMessage, this, &Mpv::handleLogMessage);

    eventManager->moveToThread(&m_eventManagerThread);
    connect(&m_eventManagerThread, &QThread::started, eventManager, &MpvEventManager::listenToEvents);
    m_eventManagerThread.start();

    setProperty("vid", MPV_FORMAT_STRING, "no");
    setProperty("sid", MPV_FORMAT_STRING, "no");

    if (handleError(initialize()))
    {
        return;
    }

    observeProperty("metadata/by-key/icy-title", MPV_FORMAT_STRING); // now playing
    observeProperty("time-pos", MPV_FORMAT_INT64);                   // elapsed
    observeProperty("volume", MPV_FORMAT_DOUBLE);                    // volume
    observeProperty("mute", MPV_FORMAT_STRING);                      // muted
}

int Mpv::create()
{
    m_mpvHandle = mpv_create();
    const int errorCode = (m_mpvHandle) ? MPV_ERROR_SUCCESS : MPV_ERROR_NOMEM;

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_create failed with error code" << MPV_ERROR_NOMEM;
    }

    return errorCode;
}

int Mpv::requestLogMessages()
{
    const char *minLogLevel = "warn";

    const int errorCode = mpv_request_log_messages(m_mpvHandle, minLogLevel);

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_request_log_messages(" << minLogLevel << ") failed with error code" << errorCode;
    }

    return errorCode;
}

int Mpv::initialize()
{
    const int errorCode = mpv_initialize(m_mpvHandle);

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_initialize failed with error code" << errorCode;
    }

    return errorCode;
}

int Mpv::command(const char *args[])
{
    const int errorCode = mpv_command(m_mpvHandle, args);

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        QStringList argsStringList;

        for (int i = 0; args[i] != NULL; ++i)
        {
            argsStringList << args[i];
        }

        qCCritical(radioMpv) << "mpv_command(" << argsStringList << ") failed with error code" << errorCode;
    }

    return errorCode;
}

int Mpv::setProperty(const char *name, const mpv_format &format, const QVariant &value)
{
    mpv_node node;

    node.format = format;

    switch (format)
    {
        case MPV_FORMAT_STRING:
        {
            node.u.string = Utilities::toCString(value.toString());

            break;
        }
        case MPV_FORMAT_DOUBLE:
        {
            bool ok;

            node.u.double_ = value.toReal(&ok);

            if (!ok)
            {
                qCFatal(radioMpv) << "value.toReal failed in setProperty";

                return false;
            }

            break;
        }
        default:
        {
            qCFatal(radioMpv) << "setProperty does not support format" << format;

            return false;
        }
    }

    const int errorCode = mpv_set_property(m_mpvHandle, name, MPV_FORMAT_NODE, &node);

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_set_property(" << name << "=" << value << ") failed with error code" << errorCode;
    }

    return errorCode;
}

int Mpv::observeProperty(const char *name, const mpv_format &format)
{
    const int errorCode = mpv_observe_property(m_mpvHandle, 0, name, format);

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_observe_property(" << name << ") failed with error code" << errorCode;
    }

    return errorCode;
}
