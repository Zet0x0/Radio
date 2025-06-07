#include "utilities.h"

#include <QCursor>

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
