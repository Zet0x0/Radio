qt_add_library(Radio_Main STATIC)

qt_add_qml_module(
    Radio_Main
    URI Radio
    VERSION 1.0
    QML_FILES Main.qml Utilities.js
    PLUGIN_TARGET Radio_Main_module
)

add_subdirectory(MainWindow)
add_subdirectory(SystemTray)
