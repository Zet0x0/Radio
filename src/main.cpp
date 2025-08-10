#include "dialogcontroller.h"
#include "player/player.h"
#include "utilities.h"

#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>

Q_LOGGING_CATEGORY(radioMain, "radio.main")

QtMessageHandler originalLogMessageHandler = nullptr;

void handleLogMessage(QtMsgType type,
                      const QMessageLogContext &context,
                      const QString &message)
{
    Utilities::handleLogMessage(type, context, message);

    if (originalLogMessageHandler)
    {
        (*originalLogMessageHandler)(type, context, message);
    }
}

int main(int argc, char *argv[])
{
    Utilities *utilities
        = Utilities::instance(); // HACK?: make sure the instance is created in
                                 // OUR thread

    qSetMessagePattern(
        "[%{if-debug}DEBUG%{endif}%{if-info}INFO%{endif}%{if-warning}WARNING%{"
        "endif}%{if-critical}CRITICAL%{endif}%{if-fatal}FATAL%{endif}] "
        "%{if-category}%{category}: %{endif}%{message}");
    originalLogMessageHandler = qInstallMessageHandler(handleLogMessage);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;

    QLocale::setDefault(QLocale::c());

    app.setQuitOnLastWindowClosed(false);

    QObject::connect(
        &qmlEngine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        [](const QUrl &url)
        {
            qCCritical(radioMain)
                << "qml object creation failed for url" << url;

            QGuiApplication::exit(1);
        },
        Qt::QueuedConnection);

    qmlEngine.addImportPath(":/zet0x0.github.io/qml/imports");
    qmlRegisterSingletonInstance("Radio.Cpp.Utilities",
                                 1,
                                 0,
                                 "Utilities",
                                 utilities);
    qmlRegisterSingletonInstance("Radio.Cpp.Utilities",
                                 1,
                                 0,
                                 "DialogController",
                                 DialogController::instance());
    qmlRegisterSingletonInstance("Radio.Cpp.Player",
                                 1,
                                 0,
                                 "Player",
                                 Player::instance());

    qmlEngine.loadFromModule("Radio", "Main");

    return app.exec();
}
