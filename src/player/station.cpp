#include "station.h"

#include "../utilities.h"

#include <QDebug>
#include <QJsonObject>
#include <QUrl>

Q_LOGGING_CATEGORY(radioObjStation, "radio.obj.station")

Station::Station(const QString &name,
                 const QString &imageUrl,
                 const QString &streamUrl)
    : m_streamUrl(streamUrl.trimmed())
{
    setName(name);
    setImageUrl(imageUrl);

    updateSetInvalid();

    connect(this, &Station::nameChanged, this, &Station::updateSetInvalid);
    connect(this, &Station::imageUrlChanged, this, &Station::updateSetInvalid);
}

QString Station::name() const
{
    return m_name;
}

void Station::setName(QString newName)
{
    newName = Utilities::escapeControlCharacters(newName.trimmed());

    if (m_name == newName)
    {
        return;
    }

    m_name = newName;

    emit nameChanged();
}

QString Station::imageUrl() const
{
    return m_imageUrl;
}

void Station::setImageUrl(QString newImageUrl)
{
    newImageUrl = newImageUrl.trimmed();

    if (newImageUrl.isEmpty())
    {
        return;
    }

    if (!QUrl(newImageUrl).isValid())
    {
        qCWarning(radioObjStation)
            << "imageUrl.isValid() returned false for" << newImageUrl;

        return;
    }

    if (m_imageUrl == newImageUrl)
    {
        return;
    }

    m_imageUrl = newImageUrl;

    emit imageUrlChanged();
}

QString Station::streamUrl() const
{
    return m_streamUrl;
}

bool Station::operator==(const Station &other) const
{
    return m_name == other.m_name && m_imageUrl == other.m_imageUrl
        && m_streamUrl == other.m_streamUrl;
}

bool Station::isInvalid() const
{
    return m_invalid;
}

Station *Station::fromJsonObject(const QJsonObject &object)
{
    return new Station(object["name"].toString(),
                       object["imageUrl"].toString(),
                       object["streamUrl"].toString());
}

QJsonObject Station::toJsonObject(Station *station)
{
    if (!station)
    {
        return QJsonObject();
    }

    return QJsonObject{
        { "name",      station->name()      },
        { "imageUrl",  station->imageUrl()  },
        { "streamUrl", station->streamUrl() }
    };
}

void Station::updateSetInvalid()
{
    const bool newInvalid = m_streamUrl.isEmpty();

    if (m_invalid == newInvalid)
    {
        return;
    }

    m_invalid = newInvalid;

    emit invalidChanged();
}

QDebug operator<<(QDebug debug, const Station &station)
{
    QDebugStateSaver saver(debug);

    debug.nospace() << "{ "
                    << "invalid = " << station.isInvalid() << ", "
                    << "name = " << station.name() << ", "
                    << "imageUrl = " << station.imageUrl() << ", "
                    << "streamUrl = " << station.streamUrl() << " }";

    return debug;
}
