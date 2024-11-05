#include "clipboard.h"
#include <QClipboard>

Q_LOGGING_CATEGORY(radio_clipboard, "radio.clipboard")

Clipboard *Clipboard::qmlInstance(QQmlEngine *, QJSEngine *)
{
    static Clipboard *instance = new Clipboard;

    return instance;
}

void Clipboard::setText(const QString &text)
{
    qCDebug(radio_clipboard) << "copying text into clipboard:" << text;

    m_clipboard->setText(text);
}
