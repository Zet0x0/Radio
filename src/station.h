#pragma once

#include <QObject>

class Station : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    // Q_PROPERTY(QString caption READ caption WRITE setCaption NOTIFY captionChanged FINAL)
    // TODO: implement that ^ sometime
    Q_PROPERTY(QString imageUrl READ imageUrl WRITE setImageUrl NOTIFY imageUrlChanged FINAL)
    Q_PROPERTY(QString streamUrl READ streamUrl WRITE setStreamUrl NOTIFY streamUrlChanged FINAL)

public:
    Station(const QString &name, const QString &imageUrl, const QString &streamUrl);

    QString name() const;
    void setName(const QString &newName);

    QString imageUrl() const;
    void setImageUrl(const QString &newImageUrl);

    QString streamUrl() const;
    void setStreamUrl(const QString &newStreamUrl);

    bool operator==(const Station &other) const;

signals:
    void nameChanged();
    void imageUrlChanged();
    void streamUrlChanged();

private:
    QString m_name;
    QString m_imageUrl;
    QString m_streamUrl;
};
