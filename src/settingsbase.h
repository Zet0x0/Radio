#pragma once

#include <QSettings>

class SettingsBase : public QSettings
{
    Q_OBJECT

protected:
    SettingsBase(const QString &filename);

    virtual QVariant getDefault(const QString &path) const = 0;

    template<typename T> T readVariant(const QString &path) const
    {
        const QVariant value = SettingsBase::value(path);

        return (contains(path) && value.canConvert<T>())
                 ? value.value<T>()
                 : getDefault(path).value<T>();
    }

    template<typename T>
    void writeVariant(const QString &path, const QVariant &newValue)
    {
        if (newValue == readVariant<T>(path))
        {
            return;
        }

        setValue(path, newValue);
    }
};
