qt_add_executable(
    ${CMAKE_PROJECT_NAME}
    main.cpp
    discord.h
    discord.cpp
    settingsbase.h
    settingsbase.cpp
    icons/icons.qrc
    qml/qml.qrc
    Radio.rc
)

qt_add_qml_module(
    Radio
    URI Radio.Cpp
    VERSION 1.0
    SOURCES
        utilities.h
        utilities.cpp
        dialogcontroller.h
        dialogcontroller.cpp
        settings.h
        settings.cpp
        stylesettings.h
        stylesettings.cpp
        networkinformation.h
        networkinformation.cpp
    RESOURCE_PREFIX /zet0x0.github.io/qml/imports
    OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Radio/Cpp"
)
