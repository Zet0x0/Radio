#include "dialogcontroller.h"
#include "networkinformation.h"
#include "player/player.h"
#include "settings.h"
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
    qSetMessagePattern(
        "[%{if-debug}DEBUG%{endif}%{if-info}INFO%{endif}%{if-warning}WARNING%{"
        "endif}%{if-critical}CRITICAL%{endif}%{if-fatal}FATAL%{endif}] "
        "%{if-category}%{category}: %{endif}%{message}");
    originalLogMessageHandler = qInstallMessageHandler(handleLogMessage);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;

    QLocale::setDefault(QLocale::c());

    Settings *settings = Settings::instance();

    QObject::connect(settings,
                     &Settings::appQuitOnWindowClosedChanged,
                     &app,
                     [&app, settings]
                     {
                         app.setQuitOnLastWindowClosed(
                             settings->appQuitOnWindowClosed()
                             || !settings->appSystemTrayVisible());
                     });
    QObject::connect(settings,
                     &Settings::appSystemTrayVisibleChanged,
                     &app,
                     [&app, settings]
                     {
                         app.setQuitOnLastWindowClosed(
                             settings->appQuitOnWindowClosed()
                             || !settings->appSystemTrayVisible());
                     });
    app.setQuitOnLastWindowClosed(settings->appQuitOnWindowClosed()
                                  || !settings->appSystemTrayVisible());

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
    qmlRegisterSingletonInstance("Radio.Cpp",
                                 1,
                                 0,
                                 "CppUtilities",
                                 Utilities::instance());
    qmlRegisterSingletonInstance("Radio.Cpp",
                                 1,
                                 0,
                                 "DialogController",
                                 DialogController::instance());
    qmlRegisterSingletonInstance("Radio.Cpp", 1, 0, "Settings", settings);
    qmlRegisterSingletonInstance("Radio.Cpp",
                                 1,
                                 0,
                                 "NetworkInformation",
                                 NetworkInformation::instance());
    qmlRegisterSingletonInstance("Radio.Cpp.Player",
                                 1,
                                 0,
                                 "Player",
                                 Player::instance());

    qmlEngine.loadFromModule("Radio", "Main");

    return app.exec();
}
