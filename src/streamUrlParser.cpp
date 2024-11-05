#include "streamUrlParser.h"
#include "networkAccessManager.h"

Q_LOGGING_CATEGORY(radio_streamUrlParser, "radio.streamUrlParser")

StreamUrlParser *StreamUrlParser::instance()
{
    static StreamUrlParser *instance = new StreamUrlParser;

    return instance;
}

void StreamUrlParser::refreshZenoFmSiteBuildId(const QString &pendingStreamUrl)
{
    m_pendingStreamUrl = pendingStreamUrl;

    if (m_refreshingZenoFmSiteBuildId)
    {
        return;
    }

    m_refreshingZenoFmSiteBuildId = true;

    qCDebug(radio_streamUrlParser) << "refreshing zeno.fm site buildId";

    QNetworkReply *reply =
        NetworkAccessManager::get(QNetworkRequest(QUrl("https://zeno.fm/search/")));

    connect(
        reply, &QNetworkReply::finished, this,
        [reply, this]
        {
            if (!NetworkAccessManager::shouldParseReply(reply))
            {
                return;
            }

            m_refreshingZenoFmSiteBuildId = false;
            const QString pendingStreamUrl = m_pendingStreamUrl;
            m_pendingStreamUrl = QString();

            const NetworkAccessManager::ParsedReply parsedReply =
                NetworkAccessManager::parseReply(reply, false);

            if (parsedReply.error != NetworkAccessManager::NoError)
            {
                const QString errorString = parsedReply.errorString;

                qCCritical(radio_streamUrlParser)
                    << "failed to refresh zeno.fm site buildId: failed to parse response:"
                    << errorString;

                emit zenoFmSiteBuildIdRefreshingErrorOccurred(pendingStreamUrl, errorString);

                return;
            }

            static const QRegularExpression zenoFmSiteBuildIdRegEx =
                QRegularExpression(R"(\"buildId\"\s*:\s*\"(.+?)\")");
            const QRegularExpressionMatch buildIdMatch =
                zenoFmSiteBuildIdRegEx.match(parsedReply.content);
            m_zenoFmSiteBuildId = buildIdMatch.captured(1);

            if (buildIdMatch.hasMatch())
            {
                qCDebug(radio_streamUrlParser)
                    << "zeno.fm site buildId refreshed:" << m_zenoFmSiteBuildId;

                beginParsing(pendingStreamUrl);

                return;
            }

            qCCritical(radio_streamUrlParser)
                << "failed to refresh zeno.fm site buildId: buildIdMatch.hasMatch() returned false";

            emit zenoFmSiteBuildIdRefreshingErrorOccurred(
                pendingStreamUrl, "Could not find the Build ID of the site.");
        });
    connect(reply, &QNetworkReply::errorOccurred, this,
            [reply, this]
            {
                m_refreshingZenoFmSiteBuildId = false;
                const QString pendingStreamUrl = m_pendingStreamUrl;
                m_pendingStreamUrl = QString();

                const QString errorString = reply->errorString();

                qCCritical(radio_streamUrlParser)
                    << "failed to refresh zeno.fm site buildId:" << errorString;

                emit zenoFmSiteBuildIdRefreshingErrorOccurred(pendingStreamUrl, errorString);
            });
}

bool StreamUrlParser::shouldParse(const QString &streamUrl)
{
    return streamUrl.startsWith("http://zeno.fm/radio/") ||
           streamUrl.startsWith("https://zeno.fm/radio/");
}

void StreamUrlParser::beginParsing(const QString &streamUrl)
{
    StreamUrlParser *instance = StreamUrlParser::instance();

    if (!shouldParse(streamUrl))
    {
        emit instance->streamUrlParsingErrorOccurred(streamUrl,
                                                     "This Stream URL shouldn't be parsed.");

        return;
    }

    abortPendingParsing();

    const QString zenoFmSiteBuildId = instance->m_zenoFmSiteBuildId;

    if (zenoFmSiteBuildId.isEmpty())
    {
        instance->refreshZenoFmSiteBuildId(streamUrl);

        return;
    }

    qCDebug(radio_streamUrlParser) << "parsing stream url" << streamUrl;

    QNetworkReply *reply = instance->m_pendingReply = NetworkAccessManager::get(QNetworkRequest(
        QUrl(QString("https://zeno.fm/_next/data/%0/radio/%1.json")
                 .arg(zenoFmSiteBuildId, streamUrl.split("/", Qt::SkipEmptyParts).last()))));

    connect(reply, &QNetworkReply::finished, instance,
            [instance, reply, streamUrl]
            {
                if (!NetworkAccessManager::shouldParseReply(reply))
                {
                    return;
                }

                const NetworkAccessManager::ParsedReply parsedReply =
                    NetworkAccessManager::parseReply(reply);

                if (parsedReply.error == NetworkAccessManager::NoError)
                {
                    const QString parsedStreamUrl =
                        parsedReply.json["pageProps"]["station"]["streamURL"].toString();

                    qCDebug(radio_streamUrlParser)
                        << "stream url" << streamUrl << "parsed:" << parsedStreamUrl;

                    emit instance->streamUrlParsingFinished(parsedStreamUrl);

                    return;
                }

                const QString errorString = parsedReply.errorString;

                qCCritical(radio_streamUrlParser).nospace()
                    << "failed to parse stream url " << streamUrl
                    << ": failed to parse response: " << errorString;

                emit instance->streamUrlParsingErrorOccurred(streamUrl, errorString);
            });
    connect(reply, &QNetworkReply::errorOccurred, instance,
            [reply, streamUrl, instance](QNetworkReply::NetworkError error)
            {
                const QString errorString = reply->errorString();

                qCCritical(radio_streamUrlParser).nospace()
                    << "failed to parse stream url " << streamUrl << ": " << errorString;

                if (error == QNetworkReply::OperationCanceledError)
                {
                    return;
                }

                if (error == QNetworkReply::ContentNotFoundError &&
                    NetworkAccessManager::parseReply(reply).json.isEmpty())
                {
                    instance->refreshZenoFmSiteBuildId(streamUrl);

                    return;
                }

                emit instance->streamUrlParsingErrorOccurred(streamUrl, errorString);
            });
    connect(reply, &QNetworkReply::destroyed, instance,
            [instance]
            {
                instance->m_pendingReply = nullptr;
            });
}

void StreamUrlParser::abortPendingParsing()
{
    QNetworkReply *pendingReply = instance()->m_pendingReply;

    if (pendingReply)
    {
        pendingReply->abort();
    }
}
