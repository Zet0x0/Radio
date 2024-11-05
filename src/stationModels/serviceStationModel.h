#pragma once

#include "stationModel.h"

class ServiceStationModel : public StationModel
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool searching MEMBER m_searching NOTIFY searchingChanged FINAL)

public slots:
    virtual void search(const QString &, const bool &newSearch = true) = 0;

protected:
    bool m_searchReachedEnd = false;
    QString m_currentSearchQuery;
    bool m_searching = false;

    QList<Station> m_stations;

    ServiceStationModel();

    void reportSearchError(const QString &);

    void setSearching(const bool &);

signals:
    void searchingChanged(const bool &);

    void errorOccurred(const QString &);
    void finished();

public:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool canFetchMore(const QModelIndex &parent) const override;
};
