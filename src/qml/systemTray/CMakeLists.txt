qt_add_library(Radio_systemTray STATIC)

qt_add_qml_module(
    Radio_systemTray
    URI Radio.SystemTray
    VERSION 1.0
    QML_FILES SystemTrayIcon.qml SystemTrayMenu.qml
    PLUGIN_TARGET Radio_systemTray_module
)
