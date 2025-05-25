qt_add_library(Radio_MainWindow STATIC)

qt_add_qml_module(
    Radio_MainWindow
    URI Radio.MainWindow
    VERSION 1.0
    QML_FILES
        MainWindow.qml
        TopLayout.qml
        BottomLayout.qml
    PLUGIN_TARGET Radio_MainWindow_module
)
