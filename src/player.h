#pragma once

#include "station.h"
#include <QLoggingCategory>
#include <QQmlEngine>
#include <vlc/vlc.h>

Q_DECLARE_LOGGING_CATEGORY(radio_player)
Q_DECLARE_LOGGING_CATEGORY(radio_player_libVlc)

class Player : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool initialized MEMBER m_initialized NOTIFY initializedChanged FINAL)
    Q_PROPERTY(bool initializationFailed MEMBER m_initializationFailed NOTIFY
                   initializationFailedChanged FINAL)
    Q_PROPERTY(QString initializationState MEMBER m_initializationState NOTIFY
                   initializationStateChanged FINAL)
    Q_PROPERTY(QString initializationDetails MEMBER m_initializationDetails NOTIFY
                   initializationDetailsChanged FINAL)

    Q_PROPERTY(Station station MEMBER m_station WRITE setStation NOTIFY stationChanged FINAL)
    Q_PROPERTY(State state MEMBER m_state NOTIFY stateChanged FINAL)
    Q_PROPERTY(QString nowPlaying MEMBER m_nowPlaying NOTIFY nowPlayingChanged FINAL)
    Q_PROPERTY(int elapsed MEMBER m_elapsed NOTIFY elapsedChanged FINAL)
    Q_PROPERTY(bool playing MEMBER m_playing NOTIFY playingChanged FINAL)
    Q_PROPERTY(bool loading MEMBER m_loading NOTIFY loadingChanged FINAL)
    Q_PROPERTY(int bufferProgress MEMBER m_bufferProgress NOTIFY bufferProgressChanged FINAL)
    Q_PROPERTY(int volume MEMBER m_volume WRITE setVolume NOTIFY volumeChanged FINAL)
    Q_PROPERTY(bool muted READ isMuted WRITE setMuted NOTIFY mutedChanged FINAL)

    Q_PROPERTY(int streamUrlIndex MEMBER m_streamUrlIndex NOTIFY streamUrlIndexChanged FINAL)

public slots:
    void beginInitialization();

    void setStation(const Station &);
    void setVolume(const int &);
    void setMuted(const bool &);

    void play();
    void stop();

private slots:
    void initialize();

public:
    enum State
    {
        OpeningState,
        BufferingState,
        PlayingState,
        PausedState,
        StoppedState,
        EndedState,
        ErrorState,
        ParsingStreamUrlState,
        UndefinedState
    };

    Q_ENUM(State)

private:
    bool m_initialized = false;
    bool m_initializationFailed = false;
    QString m_initializationState = "Current initialization state unknown.";
    QString m_initializationDetails = "You shouldn't see this.";

    libvlc_instance_t *m_libVlcInstance{};
    QStringList m_libVlcLogMessages;

    libvlc_media_player_t *m_mediaPlayer{};
    libvlc_media_list_player_t *m_mediaListPlayer{};
    libvlc_media_list_t *m_mediaList{};

    Station m_station;
    State m_state = UndefinedState;
    QString m_nowPlaying;
    int m_startedListeningAt = 0;
    int m_elapsed = 0;
    bool m_playing = false;
    bool m_loading = false;
    int m_bufferProgress = 0;
    int m_volume = 100;

    bool m_allStreamUrlsFailed = false;
    int m_streamUrlIndex = 0;

    Player();

    void initializeLibVlc();
    void setInitialized(const bool &);

    void setInitializationError(const QString &message, const QString &details = QString());
    void setInitializationFailed(const bool &);

    void setInitializationState(const QString &);
    void resetInitializationState();
    void setInitializationDetails(const QString &);
    void resetInitializationDetails();

    void reportError(const QString &title, const QString &message,
                     const QString &details = QString());

    void setNowPlaying(QString);
    void setElapsed(const int &);
    void setState(const State &);
    void setPlaying(const bool &);
    void setLoading(const bool &);
    void setBufferProgress(const int &);

    void setStreamUrlIndex(const int &);

    void play(const QString &streamUrl);

    void removeMediaFromMediaList();

    static void libVlcEventHandler(const libvlc_event_t *, void *);

    QString getLibVlcErrorMessage(const QString &defaultValue = QString());

    void updateDiscordActivity();

signals:
    void libVlcInitialized(QPrivateSignal);
    void initializedChanged(const bool &);
    void initializationFailedChanged(const bool &);
    void initializationStateChanged(const QString &);
    void initializationDetailsChanged(const QString &);

    void stationChanged(const Station &);
    void stateChanged(const Player::State &);
    void nowPlayingChanged(const QString &);
    void elapsedChanged(const int &);
    void playingChanged(const bool &);
    void loadingChanged(const bool &);
    void bufferProgressChanged(const int &);
    void volumeChanged(const int &);
    void mutedChanged(const bool &);
    void mediaStopRequested();

    void streamUrlErrorOccurred(const QString &errorString, const QString &details, QPrivateSignal);
    void streamUrlIndexChanged(const int &);

    void newLibVlcLogMessage(const QString &);

public:
    static Player *instance();
    static Player *qmlInstance(QQmlEngine *, QJSEngine *);

    static bool setEqualizer(libvlc_equalizer_t *);
    Q_INVOKABLE bool isMuted();

    Q_INVOKABLE QString getCurrentStreamUrl();

    static const QStringList libVlcLogMessages();
};
