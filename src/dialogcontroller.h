#pragma once

#include <QQmlEngine>

class DialogController : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    static DialogController *instance();
    static DialogController *create(QQmlEngine *, QJSEngine *);

    Q_INVOKABLE static void requestMessageDialog(const QString &title,
                                                 const QString &message,
                                                 const bool &quitOnClose);

    Q_INVOKABLE static void requestAboutDialog();
    Q_INVOKABLE static void requestMessagesDialog();
    Q_INVOKABLE static void requestSettingsDialog();

signals:
    void messageDialogRequested(const QString &title,
                                const QString &message,
                                const bool &quitOnClose);

    void aboutDialogRequested();
    void messagesDialogRequested();
    void settingsDialogRequested();
};
