#pragma once

#include <QPoint>
#include <QQmlEngine>

class Utilities : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    static Utilities *instance();
    static Utilities *create(QQmlEngine *, QJSEngine *);

    Q_INVOKABLE QPoint
        getGlobalCursorPos(); // https://github.com/Zet0x0/SampleCustomSystemTray

    static const char *toCString(const QString &string);
};
