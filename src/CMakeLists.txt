qt_add_executable(
    ${CMAKE_PROJECT_NAME}
    main.cpp
    icons/icons.qrc
)

qt_add_qml_module(
    Radio
    URI Radio.Cpp
    VERSION 1.0
    SOURCES utilities.h utilities.cpp
)
