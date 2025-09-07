#pragma once

#include <QPoint>
#include <QQmlEngine>

class Utilities : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_NAMED_ELEMENT(CppUtilities)

private:
    Utilities();

public:
    static Utilities *instance();
    static Utilities *create(QQmlEngine *, QJSEngine *);

    /* https://github.com/Zet0x0/SampleCustomSystemTray */
    static Q_INVOKABLE QPoint getGlobalCursorPos();

    static const char *toCString(const QString &);

    static Q_INVOKABLE void copyToClipboard(const QString &);

    static void handleLogMessage(QtMsgType,
                                 const QMessageLogContext &,
                                 const QString &message);

    static Q_INVOKABLE QString getLibMpvVersion();
    static Q_INVOKABLE QString getQtVersion();
    static Q_INVOKABLE QString getVersionSummary();

    static QString escapeControlCharacters(QString);

    Q_INVOKABLE static QString getShazamLinkFor(const QString &query);

signals:
    void logMessage(const QString &);
};
