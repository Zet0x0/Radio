qt_add_library(Radio_ApplicationStyle STATIC)

set_target_properties(Radio_ApplicationStyle PROPERTIES AUTOMOC ON)
target_link_libraries(Radio_ApplicationStyle PRIVATE Qt6::Quick)

set_source_files_properties(
    StyleProperties.qml PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)

qt_add_qml_module(
    Radio_ApplicationStyle
    URI Radio.ApplicationStyle
    VERSION 1.0
    QML_FILES
        StyleProperties.qml
        ApplicationWindow.qml
        ToolTip.qml
        Control.qml
        Button.qml
    RESOURCE_PREFIX /zet0x0.github.io/qml/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio/ApplicationStyle"
)
