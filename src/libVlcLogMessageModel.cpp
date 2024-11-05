#include "libVlcLogMessageModel.h"
#include "player.h"

LibVlcLogMessageModel::LibVlcLogMessageModel() : m_libVlcLogMessages(Player::libVlcLogMessages())
{
    connect(Player::instance(), &Player::newLibVlcLogMessage, this,
            [this](const QString &libVlcLogMessage)
            {
                const qsizetype newLastIndex = m_libVlcLogMessages.size();

                beginInsertRows(QModelIndex(), newLastIndex, newLastIndex);

                m_libVlcLogMessages << libVlcLogMessage;

                endInsertRows();
            });
}

QVariant LibVlcLogMessageModel::data(const QModelIndex &index, int role) const
{
    return (index.isValid() && role == Qt::DisplayRole) ? m_libVlcLogMessages.at(index.row())
                                                        : QVariant();
}

int LibVlcLogMessageModel::rowCount(const QModelIndex &parent) const
{
    return (parent.isValid()) ? 0 : m_libVlcLogMessages.size();
}
