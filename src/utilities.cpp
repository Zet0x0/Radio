#include "utilities.h"
#include <QCursor>

Utilities *Utilities::instance()
{
    static Utilities *instance = new Utilities;

    return instance;
}

QPoint Utilities::getGlobalCursorPos()
{
    return QCursor::pos();
}
