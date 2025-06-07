qt_add_library(Radio_Cpp_Player STATIC)

set_target_properties(Radio_Cpp_Player PROPERTIES AUTOMOC ON)
target_link_libraries(Radio_Cpp_Player PRIVATE Qt6::Quick)

qt_add_qml_module(
    Radio_Cpp_Player
    URI Radio.Cpp.Player
    VERSION 1.0
    SOURCES
        player.h
        player.cpp
        station.h
        station.cpp
        mpv.h
        mpv.cpp
        mpveventmanager.h
        mpveventmanager.cpp
        mpvnodehelper.h
        mpvnodehelper.cpp
    RESOURCE_PREFIX /zet0x0.github.io/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio/Cpp/Player"
)
