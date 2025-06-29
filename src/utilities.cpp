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
    QString typeString;

    switch (type)
    {
        case QtDebugMsg:
        {
            typeString = tr("DEBUG");

            break;
        }
        case QtWarningMsg:
        {
            typeString = tr("WARNING");

            break;
        }
        case QtCriticalMsg:
        {
            typeString = tr("CRITICAL");

            break;
        }
        case QtFatalMsg:
        {
            typeString = tr("FATAL");

            break;
        }
        case QtInfoMsg:
        {
            typeString = tr("INFO");

            break;
        }
    }

    emit instance() -> logMessage(
        QString("**[%0]** %1%2")
            .arg(typeString,
                 (context.category) ? QString("%0: ").arg(context.category)
                                    : QString(),
                 message));
}
