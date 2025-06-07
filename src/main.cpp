#include "player/mpv.h"
#include "player/player.h"
#include "utilities.h"

#include <QGuiApplication>
#include <QIcon>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

Q_LOGGING_CATEGORY(radioMain, "radio.main")

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;

    QLocale::setDefault(QLocale::c());

    QQuickStyle::setStyle("FluentWinUI3");
    app.setWindowIcon(QIcon(":/icons/applicationIconBackground.svg"));

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

    qmlEngine.addImportPath(":/zet0x0.github.io/imports");
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

    /* TESTING AREA START */
    // Mpv::instance()->play("https://www.youtube.com/watch?v=xUQxzICc3e4");
    Mpv::instance()->play("https://stream.zeno.fm/90fvpb27u18uv");
    /* TESTING AREA END */

    return app.exec();
}
