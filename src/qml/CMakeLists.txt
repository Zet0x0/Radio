qt_add_library(Radio_Main STATIC)

set_target_properties(Radio_Main PROPERTIES AUTOMOC ON)
target_link_libraries(Radio_Main PRIVATE Qt6::Quick)

qt_add_qml_module(
    Radio_Main
    URI Radio
    VERSION 1.0
    QML_FILES Main.qml Utilities.js
    RESOURCE_PREFIX /zet0x0.github.io/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio"
)

add_subdirectory(MainWindow)
add_subdirectory(SystemTray)
