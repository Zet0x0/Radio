# https://doc.qt.io/qt-6/cmake-get-started.html#structuring-projects

cmake_minimum_required(VERSION 3.22)

project(
    Radio
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.9)

link_directories(${CMAKE_SOURCE_DIR}/libmpv)
include_directories(${CMAKE_SOURCE_DIR}/libmpv/include)

add_subdirectory(src)
add_subdirectory(src/qml)

target_link_libraries(
    Radio
    PRIVATE
        # Qt
        Qt6::Quick
        Qt6::QuickControls2
        # External libs
        libmpv-2
        # Our QML modules
        Radio_Main_module
        Radio_MainWindow_module
        Radio_SystemTray_module
)

set_target_properties(Radio PROPERTIES WIN32_EXECUTABLE ON)
