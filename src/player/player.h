#pragma once

#include "mpv.h"
#include "station.h"

#include <QQmlEngine>
#include <QtQmlIntegration/qqmlintegration.h>

Q_DECLARE_LOGGING_CATEGORY(radioPlayer)

class Player : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(Station *station READ station WRITE setStation NOTIFY
                   stationChanged FINAL)

    Q_PROPERTY(
        QString nowPlaying READ nowPlaying NOTIFY nowPlayingChanged FINAL)

    Q_PROPERTY(qint64 elapsed READ elapsed WRITE setElapsed NOTIFY
                   elapsedChanged FINAL)
    Q_PROPERTY(Player::State state READ state NOTIFY stateChanged FINAL)
    Q_PROPERTY(
        qint16 volume READ volume WRITE setVolume NOTIFY volumeChanged FINAL)
    Q_PROPERTY(bool muted READ muted WRITE setMuted NOTIFY mutedChanged FINAL)
    Q_PROPERTY(qint16 maxVolume READ maxVolume NOTIFY maxVolumeChanged FINAL)

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
    void setStation(Station *);

    QString nowPlaying() const;
    void setNowPlaying(QString);

    qint64 elapsed() const;

    Player::State state() const;

    qint16 volume() const;
    Q_INVOKABLE void setVolume(const qint16 &);

    bool muted() const;
    Q_INVOKABLE void setMuted(const bool &);

    qint16 maxVolume() const;

    Q_INVOKABLE void play();
    Q_INVOKABLE void stop();

signals:
    void stationChanged();

    void nowPlayingChanged();

    void elapsedChanged();
    void stateChanged();
    void volumeChanged();
    void mutedChanged();
    void maxVolumeChanged();

private:
    Mpv *m_mpv = Mpv::instance();

    Station *m_station = new Station;

    QString m_nowPlaying;

    qint64 m_elapsed;
    Player::State m_state = Player::State::STOPPED;
    qint16 m_volume = 100;
    bool m_muted = false;
    qint16 m_maxVolume;

    Player();

    void setElapsed(const qint64 &);
    void setState(const Player::State &);
    void setMaxVolume(const qint16 &);
};
