qt_add_library(Radio_Main STATIC)

set_target_properties(Radio_Main PROPERTIES AUTOMOC ON)

qt_add_qml_module(
    Radio_Main
    URI Radio
    VERSION 1.0
    QML_FILES Main.qml Utilities.js
    RESOURCE_PREFIX /zet0x0.github.io/qml/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio"
)

add_subdirectory(MainWindow)
add_subdirectory(SystemTray)
add_subdirectory(ApplicationStyle)
add_subdirectory(Shared)
