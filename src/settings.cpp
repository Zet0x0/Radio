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
    : QSettings("settings.ini", QSettings::IniFormat)
{
}

QVariant Settings::getDefault(const QString &path) const
{
    return m_defaults[path];
}

bool Settings::readBool(const QString &path) const
{
    return (contains(path)) ? value(path).toBool() : getDefault(path).toBool();
}

void Settings::writeBool(const QString &path, const bool &newValue)
{
    if (newValue == readBool(path))
    {
        return;
    }

    setValue(path, newValue);
}

int Settings::readInt(const QString &path) const
{
    bool ok;
    const int value = Settings::value(path).toInt(&ok);

    return (contains(path) && ok) ? value : getDefault(path).toInt();
}

void Settings::writeInt(const QString &path, const int &newValue)
{
    if (newValue == readInt(path))
    {
        return;
    }

    setValue(path, newValue);
}

template<typename T> T Settings::readEnum(const QString &path) const
{
    const QMetaEnum metaEnum = QMetaEnum::fromType<T>();

    bool ok;
    const int value = Settings::value(path).toInt(&ok);

    return (contains(path) && ok && metaEnum.valueToKey(value))
             ? static_cast<T>(value)
             : static_cast<T>(getDefault(path).toInt());
}

void Settings::writeEnum(const QString &path, const int &newValue)
{
    writeInt(path, newValue);
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
    return readInt("audio/volume");
}

void Settings::setAudioVolume(const quint16 &newValue)
{
    writeInt("audio/volume", newValue);

    emit audioVolumeChanged();
}

bool Settings::audioMuted() const
{
    return readBool("audio/muted");
}

void Settings::setAudioMuted(const bool &newValue)
{
    writeBool("audio/muted", newValue);

    emit audioMutedChanged();
}

int Settings::discordReconnectInterval() const
{
    return readInt("discord/reconnectInterval");
}

void Settings::setDiscordReconnectInterval(const int &newValue)
{
    writeInt("discord/reconnectInterval", newValue);

    emit discordReconnectIntervalChanged();
}

int Settings::discordActivityUpdateInterval() const
{
    return readInt("discord/activityUpdateInterval");
}

void Settings::setDiscordActivityUpdateInterval(const int &newValue)
{
    writeInt("discord/activityUpdateInterval", newValue);

    emit discordActivityUpdateIntervalChanged();
}

bool Settings::discordEnabled() const
{
    return readBool("discord/enabled");
}

void Settings::setDiscordEnabled(const bool &newValue)
{
    writeBool("discord/enabled", newValue);

    emit discordEnabledChanged();
}

Discord::StatusDisplayType Settings::discordPrioritizedStatusDisplayType() const
{
    return readEnum<Discord::StatusDisplayType>(
        "discord/prioritizedStatusDisplayType");
}

void Settings::setDiscordPrioritizedStatusDisplayType(
    const Discord::StatusDisplayType &newValue)
{
    writeEnum("discord/prioritizedStatusDisplayType", newValue);

    emit discordPrioritizedStatusDisplayTypeChanged();
}

bool Settings::appQuitOnWindowClosed() const
{
    return readBool("app/quitOnWindowClosed");
}

void Settings::setAppQuitOnWindowClosed(const bool &newValue)
{
    writeBool("app/quitOnWindowClosed", newValue);

    emit appQuitOnWindowClosedChanged();
}

bool Settings::appSystemTrayVisible() const
{
    return readBool("app/systemTrayVisible");
}

void Settings::setAppSystemTrayVisible(const bool &newValue)
{
    writeBool("app/systemTrayVisible", newValue);

    emit appSystemTrayVisibleChanged();
}

bool Settings::appStartMinimizedToTray() const
{
    return readBool("app/startMinimizedToTray");
}

void Settings::setAppStartMinimizedToTray(const bool &newValue)
{
    writeBool("app/startMinimizedToTray", newValue);

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
    return readEnum<Player::State>("private/lastSavedPlayerState");
}

void Settings::setPrivateLastSavedPlayerState(const Player::State &newValue)
{
    writeEnum("private/lastSavedPlayerState", newValue);

    emit privateLastSavedPlayerStateChanged();
}

bool Settings::playbackResumeOnStart() const
{
    return readBool("playback/resumeOnStart");
}

void Settings::setPlaybackResumeOnStart(const bool &newValue)
{
    writeBool("playback/resumeOnStart", newValue);

    emit playbackResumeOnStartChanged();
}

bool Settings::playbackAutoPlayOnStart() const
{
    return readBool("playback/autoPlayOnStart");
}

void Settings::setPlaybackAutoPlayOnStart(const bool &newValue)
{
    writeBool("playback/autoPlayOnStart", newValue);

    emit playbackAutoPlayOnStartChanged();
}

bool Settings::playbackResumeOnBackOnline() const
{
    return readBool("playback/resumeOnBackOnline");
}

void Settings::setPlaybackResumeOnBackOnline(const bool &newValue)
{
    writeBool("playback/resumeOnBackOnline", newValue);

    emit playbackResumeOnBackOnlineChanged();
}
