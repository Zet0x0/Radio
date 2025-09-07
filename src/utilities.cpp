#include "utilities.h"

#include <QClipboard>
#include <QCursor>
#include <QGuiApplication>
#include <mpv/client.h>

Utilities::Utilities()
{
    moveToThread(QCoreApplication::instance()->thread());
}

Utilities *Utilities::instance()
{
    static Utilities *instance = new Utilities;

    return instance;
}

Utilities *Utilities::create(QQmlEngine *, QJSEngine *)
{
    return instance();
}

QPoint Utilities::getGlobalCursorPos()
{
    return QCursor::pos();
}

const char *Utilities::toCString(const QString &string)
{
    return string.toUtf8().data();
}

void Utilities::copyToClipboard(const QString &text)
{
    qGuiApp->clipboard()->setText(text);
}

void Utilities::handleLogMessage(QtMsgType type,
                                 const QMessageLogContext &context,
                                 const QString &message)
{
    emit instance() -> logMessage(qFormatLogMessage(type, context, message));
}

QString Utilities::getLibMpvVersion()
{
    const unsigned long rawLibMpvVersion = mpv_client_api_version();

    return QString("%0.%1").arg(
        QString::number((rawLibMpvVersion >> 16) & 0xFFFF),
        QString::number(rawLibMpvVersion & 0xFFFF));
}

QString Utilities::getQtVersion()
{
    return QT_VERSION_STR;
}

QString Utilities::getVersionSummary()
{
    return QString("Radio: %0 / libmpv: %1 / Qt: %2")
        .arg(QCoreApplication::applicationVersion(),
             getLibMpvVersion(),
             getQtVersion());
}

QString Utilities::escapeControlCharacters(QString string)
{
    return string.replace('\r', "\\r")
        .replace('\n', "\\n")
        .replace('\t', "\\t")
        .replace('\f', "\\f");
}

QString Utilities::getShazamLinkFor(const QString &query)
{
    return QUrl(QString("https://google.com/search?q=site:shazam.com %0")
                    .arg(QUrl::toPercentEncoding(query)))
        .toString(QUrl::FullyEncoded);
}
