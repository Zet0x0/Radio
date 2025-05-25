# https://doc.qt.io/qt-6/cmake-get-started.html#structuring-projects

CMAKE_MINIMUM_REQUIRED(VERSION 3.22)

PROJECT(
    Radio
    VERSION 0.1.0
    LANGUAGES CXX
)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_AUTORCC ON)

FIND_PACKAGE(
    Qt6 REQUIRED
    COMPONENTS
        LinguistTools
        Quick
        QuickControls2
)

QT_STANDARD_PROJECT_SETUP(REQUIRES 6.9)

LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/libmpv)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/libmpv/include)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(src/qml)

TARGET_LINK_LIBRARIES(
    Radio
    PRIVATE
        # Qt
        Qt6::Quick
        Qt6::QuickControls2
        # External libs
        libmpv-2
        # Our QML modules
        Radio_main_module
        Radio_mainWindow_module
        Radio_systemTray_module
)

SET_TARGET_PROPERTIES(Radio PROPERTIES WIN32_EXECUTABLE ON)
