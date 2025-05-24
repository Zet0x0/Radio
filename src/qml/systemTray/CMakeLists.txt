ADD_LIBRARY(Radio_systemTray STATIC)

QT_ADD_QML_MODULE(
    Radio_systemTray
    URI Radio.SystemTray
    VERSION 1.0
    QML_FILES SystemTrayIcon.qml SystemTrayMenu.qml
    PLUGIN_TARGET Radio_systemTray_module
)
