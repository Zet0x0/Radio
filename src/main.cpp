#include "utilities.h"

#include <QGuiApplication>
#include <QIcon>
#include <QLoggingCategory>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

Q_LOGGING_CATEGORY(log_main, "main")

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;

    QObject::connect(
        &qmlEngine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        [](const QUrl &url)
        {
            qCCritical(log_main) << "qml object creation failed for url" << url;

            QGuiApplication::exit(-1);
        },
        Qt::QueuedConnection);

    QQuickStyle::setStyle("FluentWinUI3");

    qmlRegisterSingletonInstance("Radio.Cpp.Utilities", 1, 0, "Utilities", Utilities::instance());

    app.setWindowIcon(QIcon(":/icons/applicationIconBackground.svg"));
    app.setQuitOnLastWindowClosed(false);

    qmlEngine.loadFromModule("Radio", "Main");

    return app.exec();
}
