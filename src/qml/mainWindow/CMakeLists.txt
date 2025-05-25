add_library(Radio_mainWindow STATIC)

qt_add_qml_module(
    Radio_mainWindow
    URI Radio.MainWindow
    VERSION 1.0
    QML_FILES
        MainWindow.qml
        TopLayout.qml
        BottomLayout.qml
    PLUGIN_TARGET Radio_mainWindow_module
)
