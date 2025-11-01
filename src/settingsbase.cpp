#include "settingsbase.h"

SettingsBase::SettingsBase(const QString &filename)
    : QSettings(filename, QSettings::IniFormat)
{
}
