#include "player/player.h"
#include "utilities.h"

#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>

Q_LOGGING_CATEGORY(radioMain, "radio.main")

int main(int argc, char *argv[])
{
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

            QGuiApplication::exit(-1);
        },
        Qt::QueuedConnection);

    qmlEngine.addImportPath(":/zet0x0.github.io/qml/imports");
    qmlRegisterSingletonInstance("Radio.Cpp.Utilities",
                                 1,
                                 0,
                                 "Utilities",
                                 Utilities::instance());
    qmlRegisterSingletonInstance("Radio.Cpp.Player",
                                 1,
                                 0,
                                 "Player",
                                 Player::instance());

    qmlEngine.loadFromModule("Radio", "Main");

    return app.exec();
}
