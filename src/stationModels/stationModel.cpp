#include "stationModel.h"

QVariant StationModel::data(const QModelIndex &index, int role,
                            const QList<Station> &stationList) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    const Station station = stationList.at(index.row());

    switch (role)
    {
        case TitleRole:
        {
            return station.title;
        }

        case ImageUrlRole:
        {
            return station.imageUrl;
        }

        case SubtitleRole:
        {
            return station.subtitle;
        }

        case StreamUrlsRole:
        {
            return station.streamUrls;
        }

        default:
        {
            return QVariant();
        }
    }
}

QHash<int, QByteArray> StationModel::roleNames() const
{
    static const QHash<int, QByteArray> roleNames{
        {TitleRole,      "title"     },
        {ImageUrlRole,   "imageUrl"  },
        {SubtitleRole,   "subtitle"  },
        {StreamUrlsRole, "streamUrls"}
    };

    return roleNames;
}
