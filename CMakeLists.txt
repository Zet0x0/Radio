cmake_minimum_required(VERSION 3.16)

project(
    Radio
    VERSION 0.1
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

find_package(
    Qt6 REQUIRED
    COMPONENTS
        Core
        Gui
        Quick
        QuickControls2
)

qt_standard_project_setup(REQUIRES 6.8)

link_directories(${CMAKE_SOURCE_DIR}/libmpv)
include_directories(${CMAKE_SOURCE_DIR}/libmpv/include)

add_subdirectory(src)
add_subdirectory(src/qml)
add_subdirectory(src/player)

set_target_properties(Radio PROPERTIES WIN32_EXECUTABLE TRUE)

target_link_libraries(
    Radio
    PRIVATE
        # Qt
        Qt6::Core
        Qt6::Gui
        Qt6::Quick
        Qt6::QuickControls2
        # External
        libmpv-2
        # Our QML plugins
        Radio_Mainplugin
        Radio_MainWindowplugin
        Radio_SystemTrayplugin
        Radio_Cpp_Playerplugin
)

include(GNUInstallDirs)
install(
    TARGETS Radio
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
