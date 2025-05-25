add_library(Radio_main STATIC)

qt_add_qml_module(
    Radio_main
    URI Radio
    VERSION 1.0
    QML_FILES Main.qml
    PLUGIN_TARGET Radio_main_module
)

add_subdirectory(mainWindow)
add_subdirectory(systemTray)
