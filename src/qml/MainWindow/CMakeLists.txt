qt_add_library(Radio_MainWindow STATIC)

set_target_properties(Radio_MainWindow PROPERTIES AUTOMOC ON)

qt_add_qml_module(
    Radio_MainWindow
    URI Radio.MainWindow
    VERSION 1.0
    QML_FILES
        MainWindow.qml
        TopLayout.qml
        BottomLayout.qml
    RESOURCE_PREFIX /zet0x0.github.io/qml/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio/MainWindow"
)
