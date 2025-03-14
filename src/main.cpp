#include <QGuiApplication>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QTranslator>

Q_LOGGING_CATEGORY(log_main, "main")

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;

    QTranslator translator;

    QObject::connect(
        &qmlEngine, &QQmlApplicationEngine::objectCreationFailed, &app,
        []
        {
            qCCritical(log_main) << "qml object creation failed";

            QGuiApplication::exit(-1);
        },
        Qt::QueuedConnection);

    if (!translator.load(":/i18n/Radio_en_US.ts")) // this should not happen
    {
        qCCritical(log_main) << "translator.load failed";

        app.exit(-1);

        return -1;
    }

    app.installTranslator(&translator);

    qmlEngine.load(":/qml/Main.qml");

    return app.exec();
}
