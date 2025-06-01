#include "station.h"

Station::Station(const QString &name, const QString &imageUrl, const QString &streamUrl)
    : m_name(name),
      m_imageUrl(imageUrl),
      m_streamUrl(streamUrl)
{
    updateSetInvalid();

    connect(this, &Station::nameChanged, this, &Station::updateSetInvalid);
    connect(this, &Station::imageUrlChanged, this, &Station::updateSetInvalid);
}

QString Station::name() const
{
    return m_name;
}

void Station::setName(const QString &newName)
{
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

void Station::setImageUrl(const QString &newImageUrl)
{
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
    return m_name == other.m_name && m_imageUrl == other.m_imageUrl && m_streamUrl == other.m_streamUrl;
}

bool Station::isInvalid() const
{
    return m_invalid;
}

void Station::updateSetInvalid()
{
    const bool newInvalid = m_name.isEmpty() && m_imageUrl.isEmpty() && m_streamUrl.isEmpty();

    if (m_invalid == newInvalid)
    {
        return;
    }

    m_invalid = newInvalid;

    emit invalidChanged();
}
