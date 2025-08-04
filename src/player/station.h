#pragma once

#include <QLoggingCategory>
#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>

Q_DECLARE_LOGGING_CATEGORY(radioStation)

class Station : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool invalid READ isInvalid NOTIFY invalidChanged FINAL)

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString imageUrl READ imageUrl WRITE setImageUrl NOTIFY
                   imageUrlChanged FINAL)
    Q_PROPERTY(QString streamUrl READ streamUrl NOTIFY streamUrlChanged FINAL)

public:
    Station(const QString &name = QString(),
            const QString &imageUrl = QString(),
            const QString &streamUrl = QString());

    QString name() const;
    void setName(QString newName);

    QString imageUrl() const;
    void setImageUrl(QString newImageUrl);

    QString streamUrl() const;

    bool operator==(const Station &other) const;

    bool isInvalid() const;

signals:
    void nameChanged();
    void imageUrlChanged();
    void streamUrlChanged();

    void invalidChanged();

private:
    bool m_invalid = true;

    QString m_name;
    QString m_imageUrl;
    QString m_streamUrl;

    void updateSetInvalid();
};

QDebug operator<<(QDebug, const Station &);
