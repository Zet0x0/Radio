#include "dialogcontroller.h"

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
