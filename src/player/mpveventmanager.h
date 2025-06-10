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
    void playerStateChanged(const Player::State &);
    void maxVolumeChanged(const qreal &);

    void errorOccurred(const int &);
    void logMessage(mpv_event_log_message *);

private:
    void handleEvent(mpv_event *);
};
