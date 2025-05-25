qt_add_library(Radio_SystemTray STATIC)

qt_add_qml_module(
    Radio_SystemTray
    URI Radio.SystemTray
    VERSION 1.0
    QML_FILES SystemTrayIcon.qml SystemTrayMenu.qml
    PLUGIN_TARGET Radio_SystemTray_module
)
