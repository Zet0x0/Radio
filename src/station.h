#pragma once

#include <QDebug>

struct Station
{
    Q_GADGET

    Q_PROPERTY(QStringList streamUrls MEMBER streamUrls FINAL)

    Q_PROPERTY(QString imageUrl MEMBER imageUrl FINAL)

    Q_PROPERTY(QString subtitle MEMBER subtitle FINAL)
    Q_PROPERTY(QString title MEMBER title FINAL)

public:
    QStringList streamUrls;

    QString imageUrl;

    QString subtitle;
    QString title;

    friend bool operator==(const Station &a, const Station &b);

    friend QDebug operator<<(QDebug debug, const Station &);

    friend size_t qHash(const Station &);
};

Q_DECLARE_METATYPE(Station)
