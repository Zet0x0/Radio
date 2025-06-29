#include "utilities.h"

#include <QClipboard>
#include <QCursor>
#include <QGuiApplication>

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
