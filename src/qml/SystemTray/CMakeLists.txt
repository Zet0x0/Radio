qt_add_library(Radio_SystemTray STATIC)

set_target_properties(Radio_SystemTray PROPERTIES AUTOMOC ON)

qt_add_qml_module(
    Radio_SystemTray
    URI Radio.SystemTray
    VERSION 1.0
    QML_FILES SystemTrayIcon.qml SystemTrayMenu.qml
    RESOURCE_PREFIX /zet0x0.github.io/qml/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio/SystemTray"
)
