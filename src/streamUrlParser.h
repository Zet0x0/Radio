#pragma once

#include <QLoggingCategory>
#include <QNetworkReply>
#include <QRegularExpression>

Q_DECLARE_LOGGING_CATEGORY(radio_streamUrlParser)

class StreamUrlParser : public QObject
{
    Q_OBJECT

private:
    bool m_refreshingZenoFmSiteBuildId = false;
    QString m_zenoFmSiteBuildId;

    QNetworkReply *m_pendingReply{};

    QString m_pendingStreamUrl;

    void refreshZenoFmSiteBuildId(const QString &pendingStreamUrl);

signals:
    void streamUrlParsingErrorOccurred(const QString &streamUrl, const QString &errorString);
    void streamUrlParsingFinished(const QString &parsedStreamUrl);

    void zenoFmSiteBuildIdRefreshingErrorOccurred(const QString &streamUrl,
                                                  const QString &errorString);

public:
    static StreamUrlParser *instance();

    static void beginParsing(const QString &);
    static bool shouldParse(const QString &);
    static void abortPendingParsing();
};
