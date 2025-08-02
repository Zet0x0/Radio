#include "utilities.h"

#include <QClipboard>
#include <QCursor>
#include <QGuiApplication>
#include <mpv/client.h>

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

QString Utilities::getVersionSummary()
{
    const unsigned long rawLibMpvVersion = mpv_client_api_version();
    const QString libMpvVersion = QString("%0.%1").arg(
        QString::number((rawLibMpvVersion >> 16) & 0xFFFF),
        QString::number(rawLibMpvVersion & 0xFFFF));

    return tr("Radio: %0 / libmpv: %1 / Qt: %2")
        .arg(QCoreApplication::applicationVersion(),
             libMpvVersion,
             QT_VERSION_STR);
}
