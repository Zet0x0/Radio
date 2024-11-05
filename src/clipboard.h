#pragma once

#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQmlEngine>

Q_DECLARE_LOGGING_CATEGORY(radio_clipboard)

class Clipboard : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public slots:
    void setText(const QString &);

private:
    QClipboard *m_clipboard = QGuiApplication::clipboard();

public:
    static Clipboard *qmlInstance(QQmlEngine *, QJSEngine *);
};
