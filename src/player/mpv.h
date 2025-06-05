#pragma once

#include <QLoggingCategory>
#include <QThread>
#include <mpv/client.h>

Q_DECLARE_LOGGING_CATEGORY(radioMpv)
Q_DECLARE_LOGGING_CATEGORY(mpv)

class Mpv : public QObject
{
    Q_OBJECT

public:
    static Mpv *instance();

    static mpv_handle *mpvHandle();

    bool play(const QString &url);
    bool stop();

    bool setVolume(const qreal &);
    bool setMuted(const bool &);

    int setProperty(const char *name,
                    const mpv_format &format,
                    const QVariant &value);
    int getProperty(const char *name,
                    const mpv_format &format,
                    QVariant *result);

private slots:
    /*
     * Returns true if errorCode != MPV_ERROR_SUCCESS and it was handled
     * accordingly, false otherwise
     */
    bool handleError(const int &errorCode);
    void handleLogMessage(mpv_event_log_message *);

private:
    mpv_handle *m_mpvHandle;
    QThread m_eventManagerThread;

    Mpv();

    mpv_node *nodeFromVariant(const mpv_format &format, const QVariant &value);
    QVariant variantFromVoidPtr(const mpv_format &format, void *data);

    int create();
    int requestLogMessages();
    int initialize();

    // NOTE: args must be terminated with NULL
    int command(const char *args[]);

    int observeProperty(const char *name, const mpv_format &format);
};
