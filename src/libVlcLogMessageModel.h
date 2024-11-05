#pragma once

#include <QAbstractListModel>
#include <QQmlEngine>

class LibVlcLogMessageModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

private:
    QStringList m_libVlcLogMessages;

public:
    LibVlcLogMessageModel();

    QVariant data(const QModelIndex &, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
};
