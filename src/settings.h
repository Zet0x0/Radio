#pragma once

#include "discord.h"
#include "player/player.h"
#include "player/station.h"
#include "settingsbase.h"

class Settings : public SettingsBase
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT

    // audio
    /* audio/volume */ Q_PROPERTY(
        quint16 audioVolume READ audioVolume WRITE setAudioVolume NOTIFY
            audioVolumeChanged FINAL)
    /* audio/muted */ Q_PROPERTY(
        bool audioMuted READ audioMuted WRITE setAudioMuted NOTIFY
            audioMutedChanged FINAL)
    // ================================

    // discord integration
    /* discord/reconnectInterval */ Q_PROPERTY(
        int discordReconnectInterval READ discordReconnectInterval WRITE
            setDiscordReconnectInterval NOTIFY discordReconnectIntervalChanged
                FINAL)
    /* discord/activityUpdateInterval */ Q_PROPERTY(
        int discordActivityUpdateInterval READ discordActivityUpdateInterval
            WRITE setDiscordActivityUpdateInterval NOTIFY
                discordActivityUpdateIntervalChanged FINAL)
    /* discord/enabled */ Q_PROPERTY(
        bool discordEnabled READ discordEnabled WRITE setDiscordEnabled NOTIFY
            discordEnabledChanged FINAL)
    /* discord/prioritizedStatusDisplayType */ Q_PROPERTY(
        Discord::StatusDisplayType discordPrioritizedStatusDisplayType READ
            discordPrioritizedStatusDisplayType WRITE
                setDiscordPrioritizedStatusDisplayType NOTIFY
                    discordPrioritizedStatusDisplayTypeChanged FINAL)
    // ================================

    // application
    /* app/quitOnWindowClosed */ Q_PROPERTY(
        bool appQuitOnWindowClosed READ appQuitOnWindowClosed WRITE
            setAppQuitOnWindowClosed NOTIFY appQuitOnWindowClosedChanged FINAL)
    /* app/systemTrayVisible */ Q_PROPERTY(
        bool appSystemTrayVisible READ appSystemTrayVisible WRITE
            setAppSystemTrayVisible NOTIFY appSystemTrayVisibleChanged FINAL)
    /* app/startMinimizedToTray */ Q_PROPERTY(
        bool appStartMinimizedToTray READ appStartMinimizedToTray WRITE
            setAppStartMinimizedToTray NOTIFY appStartMinimizedToTrayChanged
                FINAL)
    // ================================

    // private, not supposed to be edited by user
    /* private/lastSavedStation */ Q_PROPERTY(
        Station *privateLastSavedStation READ privateLastSavedStation WRITE
            setPrivateLastSavedStation NOTIFY privateLastSavedStationChanged
                FINAL)
    /* private/lastSavedPlayerState */ Q_PROPERTY(
        Player::State privateLastSavedPlayerState READ
            privateLastSavedPlayerState WRITE setPrivateLastSavedPlayerState
                NOTIFY privateLastSavedPlayerStateChanged FINAL)
    // ================================

    // playback
    /* playback/resumeOnStart */ Q_PROPERTY(
        bool playbackResumeOnStart READ playbackResumeOnStart WRITE
            setPlaybackResumeOnStart NOTIFY playbackResumeOnStartChanged FINAL)
    /* playback/autoPlayOnStart */ Q_PROPERTY(
        bool playbackAutoPlayOnStart READ playbackAutoPlayOnStart WRITE
            setPlaybackAutoPlayOnStart NOTIFY playbackAutoPlayOnStartChanged
                FINAL)
    /* playback/resumeOnBackOnline */ Q_PROPERTY(
        bool playbackResumeOnBackOnline READ playbackResumeOnBackOnline WRITE
            setPlaybackResumeOnBackOnline NOTIFY
                playbackResumeOnBackOnlineChanged FINAL)

private:
    static const QHash<QString, QVariant> m_defaults;

    Settings();

    QVariant getDefault(const QString &path) const override;

public:
    static Settings *instance();
    static Settings *create(QQmlEngine *, QJSEngine *);

    quint16 audioVolume() const;
    void setAudioVolume(const quint16 &);
    bool audioMuted() const;
    void setAudioMuted(const bool &);

    int discordReconnectInterval() const;
    void setDiscordReconnectInterval(const int &);
    int discordActivityUpdateInterval() const;
    void setDiscordActivityUpdateInterval(const int &);
    bool discordEnabled() const;
    void setDiscordEnabled(const bool &);
    Discord::StatusDisplayType discordPrioritizedStatusDisplayType() const;
    void setDiscordPrioritizedStatusDisplayType(
        const Discord::StatusDisplayType &);

    bool appQuitOnWindowClosed() const;
    void setAppQuitOnWindowClosed(const bool &);
    bool appSystemTrayVisible() const;
    void setAppSystemTrayVisible(const bool &);
    bool appStartMinimizedToTray() const;
    void setAppStartMinimizedToTray(const bool &);

    Station *privateLastSavedStation() const;
    void setPrivateLastSavedStation(Station *);
    Player::State privateLastSavedPlayerState() const;
    void setPrivateLastSavedPlayerState(const Player::State &);

    bool playbackResumeOnStart() const;
    void setPlaybackResumeOnStart(const bool &);
    bool playbackAutoPlayOnStart() const;
    void setPlaybackAutoPlayOnStart(const bool &);
    bool playbackResumeOnBackOnline() const;
    void setPlaybackResumeOnBackOnline(const bool &);

signals:
    void audioVolumeChanged();
    void audioMutedChanged();

    void discordReconnectIntervalChanged();
    void discordActivityUpdateIntervalChanged();
    void discordEnabledChanged();
    void discordPrioritizedStatusDisplayTypeChanged();

    void appQuitOnWindowClosedChanged();
    void appSystemTrayVisibleChanged();
    void appStartMinimizedToTrayChanged();

    void privateLastSavedStationChanged();
    void privateLastSavedPlayerStateChanged();

    void playbackResumeOnStartChanged();
    void playbackAutoPlayOnStartChanged();
    void playbackResumeOnBackOnlineChanged();
};
