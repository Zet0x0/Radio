qt_add_library(Radio_ApplicationStyle STATIC)

set_target_properties(Radio_ApplicationStyle PROPERTIES AUTOMOC ON)
target_link_libraries(Radio_ApplicationStyle PRIVATE Qt6::Quick)

qt_add_qml_module(
    Radio_ApplicationStyle
    URI Radio.ApplicationStyle
    VERSION 1.0
    RESOURCE_PREFIX /zet0x0.github.io/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio/ApplicationStyle"
)
