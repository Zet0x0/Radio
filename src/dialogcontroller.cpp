#include "dialogcontroller.h"

#include "utilities.h"

DialogController *DialogController::instance()
{
    static DialogController *instance = new DialogController;

    return instance;
}

DialogController *DialogController::create(QQmlEngine *, QJSEngine *)
{
    return instance();
}

void DialogController::requestMessageDialog(const QString &title,
                                            const QString &message,
                                            const bool &quitOnClose)
{
    emit instance() -> messageDialogRequested(title, message, quitOnClose);
}

void DialogController::requestAboutDialog()
{
    emit instance() -> aboutDialogRequested();
}

void DialogController::requestMessagesDialog()
{
    emit instance() -> messagesDialogRequested();
}

void DialogController::requestSettingsDialog()
{
    emit instance() -> settingsDialogRequested();
}

void DialogController::requestOpenLocationDialog(const bool &pasteFromClipboard)
{
    emit instance() -> openLocationDialogRequested(
        (pasteFromClipboard) ? Utilities::getClipboardText() : QString());
}
