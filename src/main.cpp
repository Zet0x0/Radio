#include "mpv.h"
#include "utilities.h"

#include <QGuiApplication>
#include <QIcon>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QTimer>

Q_LOGGING_CATEGORY(radioMain, "radio.main")

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;

    QLocale::setDefault(QLocale::c());

    QObject::connect(
        &qmlEngine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        [](const QUrl &url)
        {
            qCCritical(radioMain) << "qml object creation failed for url" << url;

            QGuiApplication::exit(-1);
        },
        Qt::QueuedConnection);

    qmlEngine.addImportPath(":/zet0x0.github.io/imports");
    qmlRegisterSingletonInstance("Radio.Cpp", 1, 0, "Utilities", Utilities::instance());

    QQuickStyle::setStyle("FluentWinUI3");
    app.setWindowIcon(QIcon(":/icons/applicationIconBackground.svg"));
    app.setQuitOnLastWindowClosed(false);

    qmlEngine.loadFromModule("Radio", "Main");

    Mpv::instance()->play("https://stream.zeno.fm/90fvpb27u18uv");
    QTimer::singleShot(5000, []
                       {
                           Mpv::instance()->setMuted(true);
                           Mpv::instance()->play("https://stream.rcs.revma.com/1a6hdnzbebuvv");
                       });
    QTimer::singleShot(10000, []
                       {
                           Mpv::instance()->setVolume(20);
                           Mpv::instance()->setMuted(false);
                           QTimer::singleShot(1000, []
                                              {
                                                  Mpv::instance()->setVolume(40);

                                                  QTimer::singleShot(1000, []
                                                                     {
                                                                         Mpv::instance()->setVolume(60);
                                                                         Mpv::instance()->setMuted(true);
                                                                         QTimer::singleShot(1000, []
                                                                                            {
                                                                                                Mpv::instance()->setVolume(80);
                                                                                                QTimer::singleShot(1000, []
                                                                                                                   {
                                                                                                                       Mpv::instance()->setVolume(100);
                                                                                                                       QTimer::singleShot(1000, []
                                                                                                                                          {
                                                                                                                                              Mpv::instance()->setVolume(130);
                                                                                                                                              Mpv::instance()->setMuted(false);
                                                                                                                                          });
                                                                                                                   });
                                                                                            });
                                                                     });
                                              });
                       });

    return app.exec();
}
