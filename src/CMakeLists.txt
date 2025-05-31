qt_add_executable(
    ${CMAKE_PROJECT_NAME}
    main.cpp
    icons/icons.qrc
    player.h
    player.cpp
    station.h
    station.cpp
    mpv.h
    mpv.cpp
    mpveventmanager.h
    mpveventmanager.cpp
)

qt_add_qml_module(
    Radio
    URI Radio.Cpp
    VERSION 1.0
    SOURCES utilities.h utilities.cpp
    RESOURCE_PREFIX /zet0x0.github.io/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio/Cpp"
)
