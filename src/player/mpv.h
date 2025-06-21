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

    int play(const QString &url);
    int stop();

    bool setVolume(const qint16 &);
    bool setMuted(const bool &);

    int setProperty(const QString &name, const QVariant &value);
    int getProperty(const QString &name, QVariant *result);

private slots:
    void handleLogMessage(mpv_event_log_message *);

private:
    mpv_handle *m_mpvHandle;
    QThread m_eventManagerThread;

    Mpv();

    /*
     * Returns true if errorCode != MPV_ERROR_SUCCESS and it was handled
     * accordingly, false otherwise
     */
    bool handleInitializationError(const int &errorCode);
    int create();
    int requestLogMessages();
    int initialize();

    int command(const QVariant &args, QVariant *result = nullptr);

    int observeProperty(const QString &name, const mpv_format &format);

signals:
    void initializationErrorOccurred(const int &errorCode);
};
