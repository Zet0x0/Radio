#pragma once

#include "discord.h"
#include "player/player.h"
#include "player/station.h"

#include <QQmlEngine>
#include <QSettings>

class Settings : public QSettings
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
    // ================================

    // private, not supposed to be edited by user
    /* private/savedCurrentStation */ Q_PROPERTY(
        Station *privateSavedCurrentStation READ privateSavedCurrentStation
            WRITE setPrivateSavedCurrentStation NOTIFY
                privateSavedCurrentStationChanged FINAL)
    /* private/lastSavedPlayerState */ Q_PROPERTY(
        Player::State privateLastSavedPlayerState READ
            privateLastSavedPlayerState WRITE setPrivateLastSavedPlayerState
                NOTIFY privateLastSavedPlayerStateChanged FINAL)
    // ================================

    // playback
    /* playback/resumeOnStart */ Q_PROPERTY(
        bool playbackResumeOnStart READ playbackResumeOnStart WRITE
            setPlaybackResumeOnStart NOTIFY playbackResumeOnStartChanged FINAL)

private:
    Settings();

public:
    static Settings *instance();
    static Settings *create(QQmlEngine *, QJSEngine *);

    quint16 defaultAudioVolume() const;
    quint16 audioVolume() const;
    void setAudioVolume(const quint16 &);
    bool defaultAudioMuted() const;
    bool audioMuted() const;
    void setAudioMuted(const bool &);

    int defaultDiscordReconnectInterval() const;
    int discordReconnectInterval() const;
    void setDiscordReconnectInterval(const int &);
    int defaultDiscordActivityUpdateInterval() const;
    int discordActivityUpdateInterval() const;
    void setDiscordActivityUpdateInterval(const int &);
    bool defaultDiscordEnabled() const;
    bool discordEnabled() const;
    void setDiscordEnabled(const bool &);
    Discord::StatusDisplayType
        defaultDiscordPrioritizedStatusDisplayType() const;
    Discord::StatusDisplayType discordPrioritizedStatusDisplayType() const;
    void setDiscordPrioritizedStatusDisplayType(
        const Discord::StatusDisplayType &);

    bool defaultAppQuitOnWindowClosed() const;
    bool appQuitOnWindowClosed() const;
    void setAppQuitOnWindowClosed(const bool &);
    bool defaultAppSystemTrayVisible() const;
    bool appSystemTrayVisible() const;
    void setAppSystemTrayVisible(const bool &);

    Station *defaultPrivateSavedCurrentStation() const;
    Station *privateSavedCurrentStation() const;
    void setPrivateSavedCurrentStation(Station *);
    Player::State defaultPrivateLastSavedPlayerState() const;
    Player::State privateLastSavedPlayerState() const;
    void setPrivateLastSavedPlayerState(const Player::State &);

    bool defaultPlaybackResumeOnStart() const;
    bool playbackResumeOnStart() const;
    void setPlaybackResumeOnStart(const bool &);

signals:
    void audioVolumeChanged();
    void audioMutedChanged();

    void discordReconnectIntervalChanged();
    void discordActivityUpdateIntervalChanged();
    void discordEnabledChanged();
    void discordPrioritizedStatusDisplayTypeChanged();

    void appQuitOnWindowClosedChanged();
    void appSystemTrayVisibleChanged();

    void privateSavedCurrentStationChanged();
    void privateLastSavedPlayerStateChanged();

    void playbackResumeOnStartChanged();
};
