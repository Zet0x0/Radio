#include "clipboard.h"
#include "equalizer.h"
#include "favoritesManager.h"
#include "libVlcLogMessageModel.h"
#include "networkInformation.h"
#include "nowPlayingImageProvider.h"
#include "player.h"
#include "stationModels/favoriteStationModel.h"
#include "stationModels/radioGardenServiceStationModel.h"
#include "stationModels/radioNetServiceStationModel.h"
#include "stationModels/zenoFmServiceStationModel.h"
#include "urlValidator.h"
#include "utilities.h"
#include <QApplication>
#include <QFontDatabase>
#include <QQmlApplicationEngine>
#include <QTimer>
#include <QtConcurrent/QtConcurrentRun>

Q_LOGGING_CATEGORY(radio, "radio")

int main(int argc, char **argv)
{
    qputenv("QT_QUICK_FLICKABLE_WHEEL_DECELERATION", "10000");

    QGuiApplication app(argc, argv);

    app.setFont(
        [&app]() -> QFont
        {
            if (QFontDatabase::addApplicationFont(":/assets/fonts/OCR-A.ttf") == -1)
            {
                qCCritical(radio) << "could not load the application font";

                app.exit(1);

                return QFont();
            }

            QFont font = app.font();
            font.setFamily("OCR-A");
            font.setPixelSize(12);

            return font;
        }());
    app.setQuitOnLastWindowClosed(false);

    qmlRegisterSingletonType<FavoritesManager>("Radio.Favorites", 1, 0, "FavoritesManager",
                                               &FavoritesManager::qmlInstance);
    qmlRegisterType<FavoriteStationModel>("Radio.Favorites", 1, 0, "FavoriteStationModel");

    qmlRegisterSingletonType<Equalizer>("Radio.Equalizer", 1, 0, "Equalizer",
                                        &Equalizer::qmlInstance);
    qRegisterMetaType<EqualizerBand>();

    qmlRegisterType<UrlValidator>("Radio.Validators", 1, 0, "UrlValidator");

    qmlRegisterSingletonType<Player>("Radio.Player", 1, 0, "Player", &Player::qmlInstance);
    qmlRegisterSingletonType<NowPlayingImageProvider>(
        "Radio.Player", 1, 0, "NowPlayingImageProvider", &NowPlayingImageProvider::qmlInstance);
    qmlRegisterType<LibVlcLogMessageModel>("Radio.Player", 1, 0, "LibVlcLogMessageModel");
    qRegisterMetaType<Station>();

    qmlRegisterSingletonType<Clipboard>("Radio.Clipboard", 1, 0, "Clipboard",
                                        &Clipboard::qmlInstance);

    qmlRegisterSingletonType<NetworkInformation>("Radio.Network", 1, 0, "NetworkInformation",
                                                 &NetworkInformation::qmlInstance);

    qmlRegisterType<RadioNetServiceStationModel>("Radio.ServiceStationModels", 1, 0,
                                                 "RadioNetServiceStationModel");
    qmlRegisterType<ZenoFmServiceStationModel>("Radio.ServiceStationModels", 1, 0,
                                               "ZenoFmServiceStationModel");
    qmlRegisterType<RadioGardenServiceStationModel>("Radio.ServiceStationModels", 1, 0,
                                                    "RadioGardenServiceStationModel");

    qmlRegisterSingletonType<Utilities>("Radio.CppUtilities", 1, 0, "CppUtilities",
                                        &Utilities::qmlInstance);

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        [&app]
        {
            qCCritical(radio) << "failed to create application window";

            app.exit(1);
        },
        Qt::QueuedConnection);

    QObject::connect(&engine, &QQmlApplicationEngine::exit, &app, &QGuiApplication::exit);
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);

    engine.addImportPath(":/qml");

    engine.load(":/qml/Main.qml");

    QTimer::singleShot(5000, &app,
                       [&engine, &app]
                       {
                           if (!engine.rootObjects().isEmpty())
                           {
                               return;
                           }

                           qCCritical(radio)
                               << "engine.rootObjects().isEmpty() is true after 5 seconds";

                           app.exit(1);
                       });

    Utilities::setupAppProtocol();

    return app.exec();
}
