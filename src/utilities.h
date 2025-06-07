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

    /* https://github.com/Zet0x0/SampleCustomSystemTray */
    Q_INVOKABLE QPoint getGlobalCursorPos();

    static const char *toCString(const QString &string);
};
