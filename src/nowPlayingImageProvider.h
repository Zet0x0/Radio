#pragma once

#include <QLoggingCategory>
#include <QNetworkReply>
#include <QQmlEngine>

Q_DECLARE_LOGGING_CATEGORY(radio_nowPlayingImageProvider)

class NowPlayingImageProvider : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QString currentImageUrl READ currentImageUrl NOTIFY currentImageUrlChanged FINAL)

public slots:
    void fetchImage(const QString &query);

private:
    qint64 m_accessTokenExpirationTimestampMs = 0;
    bool m_refreshingAccessToken = false;
    QString m_pendingQuery;
    QString m_accessToken;

    QNetworkReply *m_pendingReply{};

    QString m_currentImageUrl;

    NowPlayingImageProvider();

    void refreshAccessToken(const QString &pendingQuery);

    void setCurrentImageUrl(const QString &);

signals:
    void currentImageUrlChanged(const QString &);

public:
    static NowPlayingImageProvider *instance();
    static NowPlayingImageProvider *qmlInstance(QQmlEngine *, QJSEngine *);

    static const QString currentImageUrl();
};
