#pragma once

#include "player.h"

#include <QLoggingCategory>
#include <mpv/client.h>

Q_DECLARE_LOGGING_CATEGORY(radioMpvEventManager)

class MpvEventManager : public QObject
{
    Q_OBJECT

public:
    static MpvEventManager *instance();

public slots:
    void listenToEvents();

signals:
    void nowPlayingChanged(const QString &);

    void elapsedChanged(const qint64 &);
    void playerStateChanged(const PlayerState &);
    void errorOccurred(const int &);
    void logMessage(mpv_event_log_message *);

    void volumeChanged(const qreal &);
    void mutedChanged(const bool &);

private:
    void handleEvent(mpv_event *);
};
