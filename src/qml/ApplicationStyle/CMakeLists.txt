qt_add_library(Radio_ApplicationStyle STATIC)

set_target_properties(Radio_ApplicationStyle PROPERTIES AUTOMOC ON)
target_link_libraries(Radio_ApplicationStyle PRIVATE Qt6::Quick)

set_source_files_properties(
    ApplicationPalette.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(
    Radio_ApplicationStyle
    URI Radio.ApplicationStyle
    VERSION 1.0
    QML_FILES ApplicationPalette.qml ApplicationWindow.qml
    RESOURCE_PREFIX /zet0x0.github.io/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio/ApplicationStyle"
)
