#include "utilities.h"
#include <QGuiApplication>
#include <QIcon>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QTranslator>

Q_LOGGING_CATEGORY(log_main, "main")

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;

    QTranslator translator;

    QObject::connect(
        &qmlEngine, &QQmlApplicationEngine::objectCreationFailed, &app,
        [](const QUrl &url)
        {
            qCCritical(log_main) << "qml object creation failed for url" << url;

            QGuiApplication::exit(-1);
        },
        Qt::QueuedConnection);

    if (!translator.load(":/i18n/Radio_en_US.ts")) // this should not happen
    {
        qCCritical(log_main) << "translator.load failed";

        app.exit(-1);

        return -1;
    }

    QQuickStyle::setStyle("FluentWinUI3");

    qmlRegisterSingletonInstance("Radio.Cpp.Utilities", 1, 0, "Utilities", Utilities::instance());

    app.setWindowIcon(QIcon(":/icons/applicationIconBackground.svg"));
    app.installTranslator(&translator);
    app.setQuitOnLastWindowClosed(false);

    qmlEngine.loadFromModule("Radio", "Main");

    return app.exec();
}
