#pragma once

#include "mpv.h"
#include "station.h"

#include <QQmlEngine>
#include <QtQmlIntegration/qqmlintegration.h>

class Player : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(Station *station READ station WRITE setStation NOTIFY stationChanged FINAL)

    Q_PROPERTY(QString nowPlaying READ nowPlaying WRITE setNowPlaying NOTIFY nowPlayingChanged FINAL)

    Q_PROPERTY(qint64 elapsed READ elapsed WRITE setElapsed NOTIFY elapsedChanged FINAL)
    Q_PROPERTY(Player::State state READ state WRITE setState NOTIFY stateChanged FINAL)
    Q_PROPERTY(qreal volume READ volume WRITE setVolume NOTIFY volumeChanged FINAL)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged FINAL)

public:
    enum State
    {
        STOPPED,
        LOADING,
        PLAYING
    };
    Q_ENUM(State)

    static Player *instance();
    static Player *create(QQmlEngine *, QJSEngine *);

    Station *station() const;
    void setStation(Station *newStation);

    QString nowPlaying() const;
    void setNowPlaying(const QString &newNowPlaying);

    qint64 elapsed() const;
    void setElapsed(const qint64 &newElapsed);

    Player::State state() const;

    qreal volume() const;
    void setVolume(const qreal &newVolume);

    bool muted() const;
    Q_INVOKABLE void setMuted(const bool &newMuted);

signals:
    void stationChanged();

    void nowPlayingChanged();

    void elapsedChanged();
    void stateChanged();
    void volumeChanged();
    void mutedChanged();

private:
    Mpv *m_mpv = Mpv::instance();

    Station *m_station = new Station;

    QString m_nowPlaying;
    qint64 m_elapsed;
    Player::State m_state = Player::State::STOPPED;

    qreal m_volume = 100.0;
    bool m_muted = false;

    Player();

    void setState(const Player::State &newState);
};
