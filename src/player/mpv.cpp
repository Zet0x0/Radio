#include "mpv.h"

#include "../utilities.h"
#include "mpveventmanager.h"
#include "mpvnodehelper.h"

#include <QVariant>

#define printMpvLogMessage(debug, prefix, text) \
    debug.noquote().nospace() << '[' << prefix << "] " << text.trimmed()

Q_LOGGING_CATEGORY(radioMpv, "radio.mpv")
Q_LOGGING_CATEGORY(mpv, "mpv")

Mpv *Mpv::instance()
{
    static Mpv *instance = new Mpv;

    return instance;
}

mpv_handle *Mpv::mpvHandle()
{
    return instance()->m_mpvHandle;
}

int Mpv::play(const QString &url)
{
    return command(QStringList({ "loadfile", url }));
}

int Mpv::stop()
{
    return command(QStringList({ "stop" }));
}

bool Mpv::setVolume(const qint16 &volume)
{
    return setProperty("volume", volume) == MPV_ERROR_SUCCESS;
}

bool Mpv::setMuted(const bool &muted)
{
    return setProperty("mute", (muted) ? "yes" : "no") == MPV_ERROR_SUCCESS;
}

int Mpv::setProperty(const QString &name, const QVariant &value)
{
    MpvNodeBuilder node(value);

    const int errorCode = mpv_set_property(m_mpvHandle,
                                           Utilities::toCString(name),
                                           MPV_FORMAT_NODE,
                                           node.node());

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_set_property(" << name << '=' << value
                             << ") failed with error code" << errorCode;
    }

    return errorCode;
}

int Mpv::getProperty(const QString &name, QVariant *result)
{
    mpv_node resultNode;

    int errorCode = mpv_get_property(m_mpvHandle,
                                     Utilities::toCString(name),
                                     MPV_FORMAT_NODE,
                                     &resultNode);

    MpvNodeAutoFree _(&resultNode);
    *result = nodeToVariant(&resultNode);

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_get_property(" << name
                             << ") failed with error code" << errorCode;
    }

    return errorCode;
}

int Mpv::initialize()
{
    if (m_initialized)
    {
        qCWarning(radioMpv)
            << "attempted to do Mpv::initialize while m_initialized is true";

        return MPV_ERROR_GENERIC;
    }

    const int createHandleResult = createHandle();

    if (createHandleResult != MPV_ERROR_SUCCESS)
    {
        return createHandleResult;
    }

    requestLogMessages();

    MpvEventManager *eventManager = MpvEventManager::instance();

    connect(eventManager,
            &MpvEventManager::logMessage,
            this,
            &Mpv::handleLogMessage);

    eventManager->moveToThread(&m_eventManagerThread);
    connect(&m_eventManagerThread,
            &QThread::started,
            eventManager,
            &MpvEventManager::listenToEvents);
    m_eventManagerThread.start();

    const int initializeHandleResult = initializeHandle();

    if (initializeHandleResult != MPV_ERROR_SUCCESS)
    {
        return initializeHandleResult;
    }

    setProperty("title", Utilities::toCString(tr("Radio")));
    setProperty("vid", "no");
    setProperty("sid", "no");

    observeProperty("media-title", MPV_FORMAT_STRING); /* nowPlaying */
    observeProperty("time-pos", MPV_FORMAT_INT64);     /* elapsed */

    m_initialized = true;

    qCInfo(radioMpv) << "initialized";

    return MPV_ERROR_SUCCESS;
}

void Mpv::handleLogMessage(const mpv_log_level &logLevel,
                           const QString &prefix,
                           const QString &text)
{
    switch (logLevel)
    {
        // libmpv does not seem to let us know if the situation is actually
        // fatal and aborting or just as critical and powerless as
        // MPV_LOG_LEVEL_ERROR, so we just make these two equal to one lesser
        // powerful
        case MPV_LOG_LEVEL_FATAL:
        case MPV_LOG_LEVEL_ERROR:
        {
            printMpvLogMessage(qCCritical(mpv), prefix, text);

            break;
        }
        case MPV_LOG_LEVEL_WARN:
        {
            printMpvLogMessage(qCWarning(mpv), prefix, text);

            break;
        }
        case MPV_LOG_LEVEL_DEBUG:
        {
            printMpvLogMessage(qCDebug(mpv), prefix, text);

            break;
        }

        case MPV_LOG_LEVEL_INFO:
        case MPV_LOG_LEVEL_V:
        case MPV_LOG_LEVEL_TRACE:
        default:
        {
            printMpvLogMessage(qCInfo(mpv), prefix, text);

            break;
        }
    }
}

int Mpv::createHandle()
{
    m_mpvHandle = mpv_create();
    const int errorCode = (m_mpvHandle) ? MPV_ERROR_SUCCESS : MPV_ERROR_NOMEM;

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv)
            << "mpv_create failed with error code" << MPV_ERROR_NOMEM;
    }

    return errorCode;
}

int Mpv::requestLogMessages()
{
    const char *minLogLevel = "warn";

    const int errorCode = mpv_request_log_messages(m_mpvHandle, minLogLevel);

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_request_log_messages(" << minLogLevel
                             << ") failed with error code" << errorCode;
    }

    return errorCode;
}

int Mpv::initializeHandle()
{
    const int errorCode = mpv_initialize(m_mpvHandle);

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv)
            << "mpv_initialize failed with error code" << errorCode;
    }

    return errorCode;
}

int Mpv::command(const QVariant &args, QVariant *result)
{
    MpvNodeBuilder argsNode(args);
    mpv_node resultNode;

    const int errorCode
        = mpv_command_node(m_mpvHandle, argsNode.node(), &resultNode);

    MpvNodeAutoFree _(&resultNode);

    if (result)
    {
        *result = nodeToVariant(&resultNode);
    }

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_command_node(" << args
                             << ") failed with error code" << errorCode;
    }

    return errorCode;
}

int Mpv::observeProperty(const QString &name, const mpv_format &format)
{
    const int errorCode = mpv_observe_property(m_mpvHandle,
                                               0,
                                               Utilities::toCString(name),
                                               format);

    if (errorCode != MPV_ERROR_SUCCESS)
    {
        qCCritical(radioMpv) << "mpv_observe_property(" << name
                             << ") failed with error code" << errorCode;
    }

    return errorCode;
}
