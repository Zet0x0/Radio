#pragma once

#include "station.h"
#include <QLoggingCategory>
#include <QQmlEngine>

Q_DECLARE_LOGGING_CATEGORY(radio_utility)

class Utilities : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public slots:
    void executeProgram(const QString &program, const QStringList &arguments);

private:
    static Utilities *instance();

signals:
    void messageDialogRequested(const QString &title, const QString &message,
                                const QString &details);

public:
    static Utilities *qmlInstance(QQmlEngine *, QJSEngine *);

    static void requestMessageDialog(const QString &title, const QString &message,
                                     const QString &details = QString());

    static const QJsonDocument parseJson(const QByteArray &, QString &errorString);

    Q_INVOKABLE static const Station stationFromJson(const QJsonObject &);

    Q_INVOKABLE const QPoint getGlobalMousePosition();

    static const QString sanitizeString(QString);

    Q_INVOKABLE const QString libVlcVersion();
    Q_INVOKABLE const QString qtVersion();

    static void setupAppProtocol();
};
