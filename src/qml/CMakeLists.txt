ADD_LIBRARY(Radio_main STATIC)

QT_ADD_QML_MODULE(
    Radio_main
    URI Radio
    VERSION 1.0
    QML_FILES Main.qml
    PLUGIN_TARGET Radio_main_module
)

ADD_SUBDIRECTORY(mainWindow)
ADD_SUBDIRECTORY(systemTray)
