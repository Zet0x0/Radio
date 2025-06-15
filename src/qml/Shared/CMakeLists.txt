qt_add_library(Radio_Shared STATIC)

set_target_properties(Radio_Shared PROPERTIES AUTOMOC ON)
target_link_libraries(Radio_Shared PRIVATE Qt6::Quick)

qt_add_qml_module(
    Radio_Shared
    URI Radio.Shared
    VERSION 1.0
    QML_FILES VolumeSlider.qml
    RESOURCE_PREFIX /zet0x0.github.io/qml/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio/Shared"
)
