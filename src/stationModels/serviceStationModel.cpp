#include "serviceStationModel.h"

ServiceStationModel::ServiceStationModel()
{
    connect(this, &ServiceStationModel::finished, this,
            [this]
            {
                setSearching(false);
            });
}

void ServiceStationModel::reportSearchError(const QString &errorString)
{
    setSearching(false);

    emit errorOccurred(errorString);
}

int ServiceStationModel::rowCount(const QModelIndex &parent) const
{
    return (parent.isValid()) ? 0 : m_stations.size();
}

bool ServiceStationModel::canFetchMore(const QModelIndex &parent) const
{
    return !parent.isValid() && !m_searching && !m_currentSearchQuery.isEmpty() &&
           !m_searchReachedEnd;
}

void ServiceStationModel::setSearching(const bool &searching)
{
    if (searching == m_searching)
    {
        return;
    }

    m_searching = searching;

    emit searchingChanged(searching);
}

QVariant ServiceStationModel::data(const QModelIndex &index, int role) const
{
    return StationModel::data(index, role, m_stations);
}
