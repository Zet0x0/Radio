#pragma once

#include <QQmlEngine>
#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT

    /* audio */
    Q_PROPERTY(quint16 audioVolume READ audioVolume WRITE setAudioVolume NOTIFY
                   audioVolumeChanged FINAL)
    Q_PROPERTY(bool audioMuted READ audioMuted WRITE setAudioMuted NOTIFY
                   audioMutedChanged FINAL)

    /* discord integration */
    Q_PROPERTY(int discordReconnectInterval READ discordReconnectInterval WRITE
                   setDiscordReconnectInterval NOTIFY
                       discordReconnectIntervalChanged FINAL)
    Q_PROPERTY(
        int discordActivityUpdateInterval READ discordActivityUpdateInterval
            WRITE setDiscordActivityUpdateInterval NOTIFY
                discordActivityUpdateIntervalChanged FINAL)
    Q_PROPERTY(bool discordEnabled READ discordEnabled WRITE setDiscordEnabled
                   NOTIFY discordEnabledChanged FINAL)

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

signals:
    void audioVolumeChanged();
    void audioMutedChanged();

    void discordReconnectIntervalChanged();
    void discordActivityUpdateIntervalChanged();
    void discordEnabledChanged();
};
