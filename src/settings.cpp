#include "settings.h"

const QHash<QString, QVariant> Settings::m_defaults = {
    { "audio/volume",                         100              },
    { "audio/muted",                          false            },
    { "discord/reconnectInterval",            5000             },
    { "discord/activityUpdateInterval",       30000            },
    { "discord/enabled",                      true             },
    { "discord/prioritizedStatusDisplayType", Discord::DETAILS },
    { "app/quitOnWindowClosed",               false            },
    { "app/systemTrayVisible",                true             },
    { "app/startMinimizedToTray",             false            },
    // { "private/lastSavedStation",             new Station      },
    { "private/lastSavedPlayerState",         Player::STOPPED  },
    { "playback/resumeOnStart",               false            },
    { "playback/autoPlayOnStart",             false            },
    { "playback/resumeOnBackOnline",          true             }
};

Settings::Settings()
    : SettingsBase("settings.ini")
{
}

QVariant Settings::getDefault(const QString &path) const
{
    return m_defaults.value(path);
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

quint16 Settings::audioVolume() const
{
    return readVariant<quint16>("audio/volume");
}

void Settings::setAudioVolume(const quint16 &newValue)
{
    writeVariant<quint16>("audio/volume", newValue);

    emit audioVolumeChanged();
}

bool Settings::audioMuted() const
{
    return readVariant<bool>("audio/muted");
}

void Settings::setAudioMuted(const bool &newValue)
{
    writeVariant<bool>("audio/muted", newValue);

    emit audioMutedChanged();
}

int Settings::discordReconnectInterval() const
{
    return readVariant<int>("discord/reconnectInterval");
}

void Settings::setDiscordReconnectInterval(const int &newValue)
{
    writeVariant<int>("discord/reconnectInterval", newValue);

    emit discordReconnectIntervalChanged();
}

int Settings::discordActivityUpdateInterval() const
{
    return readVariant<int>("discord/activityUpdateInterval");
}

void Settings::setDiscordActivityUpdateInterval(const int &newValue)
{
    writeVariant<int>("discord/activityUpdateInterval", newValue);

    emit discordActivityUpdateIntervalChanged();
}

bool Settings::discordEnabled() const
{
    return readVariant<bool>("discord/enabled");
}

void Settings::setDiscordEnabled(const bool &newValue)
{
    writeVariant<bool>("discord/enabled", newValue);

    emit discordEnabledChanged();
}

Discord::StatusDisplayType Settings::discordPrioritizedStatusDisplayType() const
{
    return readVariant<Discord::StatusDisplayType>(
        "discord/prioritizedStatusDisplayType");
}

void Settings::setDiscordPrioritizedStatusDisplayType(
    const Discord::StatusDisplayType &newValue)
{
    writeVariant<Discord::StatusDisplayType>(
        "discord/prioritizedStatusDisplayType",
        newValue);

    emit discordPrioritizedStatusDisplayTypeChanged();
}

bool Settings::appQuitOnWindowClosed() const
{
    return readVariant<bool>("app/quitOnWindowClosed");
}

void Settings::setAppQuitOnWindowClosed(const bool &newValue)
{
    writeVariant<bool>("app/quitOnWindowClosed", newValue);

    emit appQuitOnWindowClosedChanged();
}

bool Settings::appSystemTrayVisible() const
{
    return readVariant<bool>("app/systemTrayVisible");
}

void Settings::setAppSystemTrayVisible(const bool &newValue)
{
    writeVariant<bool>("app/systemTrayVisible", newValue);

    emit appSystemTrayVisibleChanged();
}

bool Settings::appStartMinimizedToTray() const
{
    return readVariant<bool>("app/startMinimizedToTray");
}

void Settings::setAppStartMinimizedToTray(const bool &newValue)
{
    writeVariant<bool>("app/startMinimizedToTray", newValue);

    emit appStartMinimizedToTrayChanged();
}

Station *Settings::privateLastSavedStation() const
{
    Station *lastSavedStation = Station::fromJsonObject(
        value("private/lastSavedStation").toJsonObject());

    return (contains("private/lastSavedStation")
            && !lastSavedStation->isInvalid())
             ? lastSavedStation
             : new Station;
}

void Settings::setPrivateLastSavedStation(Station *newValue)
{
    Station *currentLastSavedStation = privateLastSavedStation();

    if (newValue == currentLastSavedStation)
    {
        return;
    }

    setValue("private/lastSavedStation", Station::toJsonObject(newValue));

    currentLastSavedStation->deleteLater();

    emit privateLastSavedStationChanged();
}

Player::State Settings::privateLastSavedPlayerState() const
{
    return readVariant<Player::State>("private/lastSavedPlayerState");
}

void Settings::setPrivateLastSavedPlayerState(const Player::State &newValue)
{
    writeVariant<Player::State>("private/lastSavedPlayerState", newValue);

    emit privateLastSavedPlayerStateChanged();
}

bool Settings::playbackResumeOnStart() const
{
    return readVariant<bool>("playback/resumeOnStart");
}

void Settings::setPlaybackResumeOnStart(const bool &newValue)
{
    writeVariant<bool>("playback/resumeOnStart", newValue);

    emit playbackResumeOnStartChanged();
}

bool Settings::playbackAutoPlayOnStart() const
{
    return readVariant<bool>("playback/autoPlayOnStart");
}

void Settings::setPlaybackAutoPlayOnStart(const bool &newValue)
{
    writeVariant<bool>("playback/autoPlayOnStart", newValue);

    emit playbackAutoPlayOnStartChanged();
}

bool Settings::playbackResumeOnBackOnline() const
{
    return readVariant<bool>("playback/resumeOnBackOnline");
}

void Settings::setPlaybackResumeOnBackOnline(const bool &newValue)
{
    writeVariant<bool>("playback/resumeOnBackOnline", newValue);

    emit playbackResumeOnBackOnlineChanged();
}
