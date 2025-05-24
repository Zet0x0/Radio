ADD_LIBRARY(Radio_mainWindow STATIC)

QT_ADD_QML_MODULE(
    Radio_mainWindow
    URI Radio.MainWindow
    VERSION 1.0
    QML_FILES
        MainWindow.qml
        TopLayout.qml
        BottomLayout.qml
    PLUGIN_TARGET Radio_mainWindow_module
)
