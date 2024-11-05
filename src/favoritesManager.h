#pragma once

#include "station.h"
#include <QLoggingCategory>
#include <QQmlEngine>

Q_DECLARE_LOGGING_CATEGORY(radio_favoritesManager)

class FavoritesManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(
        QList<Station> favorites MEMBER m_favorites READ favorites NOTIFY favoritesChanged FINAL)

public slots:
    void removeStation(const Station &);
    void addStation(const Station &);

    void synchronizeWithFile();

private:
    QList<Station> m_favorites;

    FavoritesManager();

    bool writeToFile(const QList<Station> &favorites);

signals:
    void stationRemoved(const Station &, const qsizetype &index);
    void stationAdded(const Station &, const qsizetype &index);

    void favoritesChanged(const QList<Station> &);

public:
    static FavoritesManager *instance();
    static FavoritesManager *qmlInstance(QQmlEngine *, QJSEngine *);

    Q_INVOKABLE static const QList<Station> favorites();

    Q_INVOKABLE const QString favoritesFilePath();
};
