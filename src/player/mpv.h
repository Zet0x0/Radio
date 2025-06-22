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

    int initialize();

private slots:
    void handleLogMessage(const mpv_log_level &,
                          const QString &prefix,
                          const QString &text);

private:
    mpv_handle *m_mpvHandle;
    QThread m_eventManagerThread;

    bool m_initialized = false;

    int createHandle();
    int requestLogMessages();
    int initializeHandle();

    int command(const QVariant &args, QVariant *result = nullptr);

    int observeProperty(const QString &name, const mpv_format &format);
};
