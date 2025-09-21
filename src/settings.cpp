#include "settings.h"

Settings::Settings()
    : QSettings("settings.ini", QSettings::IniFormat)
{
}

Settings *Settings::instance()
{
    static Settings *instance = new Settings;

    return instance;
}

Settings *Settings::create(QQmlEngine *, QJSEngine *)
{
    return instance();
}

quint16 Settings::defaultAudioVolume() const
{
    return 100;
}

quint16 Settings::audioVolume() const
{
    bool ok;
    quint16 result = value("audio/volume").toUInt(&ok);

    return (contains("audio/volume") && ok) ? result : defaultAudioVolume();
}

void Settings::setAudioVolume(const quint16 &volume)
{
    if (volume == audioVolume())
    {
        return;
    }

    setValue("audio/volume", volume);

    emit audioVolumeChanged();
}

bool Settings::defaultAudioMuted() const
{
    return false;
}

bool Settings::audioMuted() const
{
    return (contains("audio/muted")) ? value("audio/muted").toBool()
                                     : defaultAudioMuted();
}

void Settings::setAudioMuted(const bool &muted)
{
    if (muted == audioMuted())
    {
        return;
    }

    setValue("audio/muted", muted);

    emit audioMutedChanged();
}

int Settings::defaultDiscordReconnectInterval() const
{
    return 5000;
}

int Settings::discordReconnectInterval() const
{
    bool ok;
    int result = value("discord/reconnectInterval").toInt(&ok);

    return (contains("discord/reconnectInterval") && ok)
             ? result
             : defaultDiscordReconnectInterval();
}

void Settings::setDiscordReconnectInterval(const int &reconnectInterval)
{
    if (reconnectInterval == discordReconnectInterval())
    {
        return;
    }

    setValue("discord/reconnectInterval", reconnectInterval);

    emit discordReconnectIntervalChanged();
}

int Settings::defaultDiscordActivityUpdateInterval() const
{
    return 30000;
}

int Settings::discordActivityUpdateInterval() const
{
    bool ok;
    int result = value("discord/activityUpdateInterval").toInt(&ok);

    return (contains("discord/activityUpdateInterval") && ok)
             ? result
             : defaultDiscordActivityUpdateInterval();
}

void Settings::setDiscordActivityUpdateInterval(
    const int &activityUpdateInterval)
{
    if (activityUpdateInterval == discordActivityUpdateInterval())
    {
        return;
    }

    setValue("discord/activityUpdateInterval", activityUpdateInterval);

    emit discordActivityUpdateIntervalChanged();
}

bool Settings::defaultDiscordEnabled() const
{
    return true;
}

bool Settings::discordEnabled() const
{
    return (contains("discord/enabled")) ? value("discord/enabled").toBool()
                                         : defaultDiscordEnabled();
}

void Settings::setDiscordEnabled(const bool &enabled)
{
    if (enabled == discordEnabled())
    {
        return;
    }

    setValue("discord/enabled", enabled);

    emit discordEnabledChanged();
}

Discord::StatusDisplayType
    Settings::defaultDiscordPrioritizedStatusDisplayType() const
{
    return Discord::DETAILS;
}

Discord::StatusDisplayType Settings::discordPrioritizedStatusDisplayType() const
{
    const QVariant rawValue = value("discord/prioritizedStatusDisplayType");
    Discord::StatusDisplayType result
        = defaultDiscordPrioritizedStatusDisplayType();

    if (contains("discord/prioritizedStatusDisplayType")
        && rawValue.canConvert<Discord::StatusDisplayType>())
    {
        result = rawValue.value<Discord::StatusDisplayType>();
    }

    return result;
}

void Settings::setDiscordPrioritizedStatusDisplayType(
    const Discord::StatusDisplayType &prioritizedStatusDisplayType)
{
    if (prioritizedStatusDisplayType == discordPrioritizedStatusDisplayType())
    {
        return;
    }

    setValue("discord/prioritizedStatusDisplayType",
             prioritizedStatusDisplayType);

    emit discordPrioritizedStatusDisplayTypeChanged();
}

bool Settings::defaultAppQuitOnWindowClosed() const
{
    return false;
}

bool Settings::appQuitOnWindowClosed() const
{
    return (contains("app/quitOnWindowClosed"))
             ? value("app/quitOnWindowClosed").toBool()
             : defaultAppQuitOnWindowClosed();
}

void Settings::setAppQuitOnWindowClosed(const bool &quitOnWindowClosed)
{
    if (quitOnWindowClosed == appQuitOnWindowClosed())
    {
        return;
    }

    setValue("app/quitOnWindowClosed", quitOnWindowClosed);

    emit appQuitOnWindowClosedChanged();
}

bool Settings::defaultAppSystemTrayVisible() const
{
    return true;
}

bool Settings::appSystemTrayVisible() const
{
    return (contains("app/systemTrayVisible"))
             ? value("app/systemTrayVisible").toBool()
             : defaultAppSystemTrayVisible();
}

void Settings::setAppSystemTrayVisible(const bool &systemTrayVisible)
{
    if (systemTrayVisible == appSystemTrayVisible())
    {
        return;
    }

    setValue("app/systemTrayVisible", systemTrayVisible);

    emit appSystemTrayVisibleChanged();
}

Station *Settings::defaultPrivateSavedCurrentStation() const
{
    return new Station;
}

Station *Settings::privateSavedCurrentStation() const
{
    Station *result = Station::fromJsonObject(
        value("private/savedCurrentStation").toJsonObject());

    return (contains("private/savedCurrentStation") && !result->isInvalid())
             ? result
             : defaultPrivateSavedCurrentStation();
}

void Settings::setPrivateSavedCurrentStation(Station *savedCurrentStation)
{
    Station *currentSavedCurrentStation = privateSavedCurrentStation();

    if (savedCurrentStation == currentSavedCurrentStation)
    {
        return;
    }

    setValue("private/savedCurrentStation",
             Station::toJsonObject(savedCurrentStation));

    currentSavedCurrentStation->deleteLater();

    emit privateSavedCurrentStationChanged();
}

Player::State Settings::defaultPrivateLastSavedPlayerState() const
{
    return Player::STOPPED;
}

Player::State Settings::privateLastSavedPlayerState() const
{
    const QVariant rawValue = value("private/lastSavedPlayerState");
    Player::State result = defaultPrivateLastSavedPlayerState();

    if (contains("private/lastSavedPlayerState")
        && rawValue.canConvert<Player::State>())
    {
        result = rawValue.value<Player::State>();
    }

    return result;
}

void Settings::setPrivateLastSavedPlayerState(
    const Player::State &lastSavedPlayerState)
{
    if (lastSavedPlayerState == privateLastSavedPlayerState())
    {
        return;
    }

    setValue("private/lastSavedPlayerState", lastSavedPlayerState);

    emit privateLastSavedPlayerStateChanged();
}

bool Settings::defaultPlaybackResumeOnStart() const
{
    return false;
}

bool Settings::playbackResumeOnStart() const
{
    return (contains("playback/resumeOnStart"))
             ? value("playback/resumeOnStart").toBool()
             : defaultPlaybackResumeOnStart();
}

void Settings::setPlaybackResumeOnStart(const bool &resumeOnStart)
{
    if (resumeOnStart == playbackResumeOnStart())
    {
        return;
    }

    setValue("playback/resumeOnStart", resumeOnStart);

    emit playbackResumeOnStartChanged();
}
