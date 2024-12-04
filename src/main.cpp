#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QTranslator>

Q_LOGGING_CATEGORY(log_main, "main")

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QTranslator translator;

    if (translator.load(":/translations/Radio_en_US"))
    {
        app.installTranslator(&translator);
    }
    else // this should not happen
    {
        qCCritical(log_main) << "translator.load failed";

        app.exit(-1);

        return -1;
    }

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []()
        {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.loadFromModule("Radio", "Main");

    return app.exec();
}
