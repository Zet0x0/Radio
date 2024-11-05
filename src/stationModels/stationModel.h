#pragma once

#include "../station.h"
#include <QAbstractListModel>
#include <QQmlEngine>

class StationModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

protected:
    QVariant data(const QModelIndex &, int role, const QList<Station> &) const;

private:
    enum Roles
    {
        TitleRole = Qt::UserRole,
        ImageUrlRole,
        SubtitleRole,
        StreamUrlsRole
    };

public:
    QHash<int, QByteArray> roleNames() const override;
};
