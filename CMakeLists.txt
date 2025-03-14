# https://doc.qt.io/qt-6/cmake-get-started.html#structuring-projects

cmake_minimum_required(VERSION 3.16)

project(Radio VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS LinguistTools Quick)
qt_standard_project_setup(REQUIRES 6.8)

# Run the update_translations CMake target to update translation strings
qt_add_translations(Radio
    TS_FILES
        i18n/Radio_en_US.ts
    LRELEASE_OPTIONS
        -idbased
)

add_subdirectory(src)

target_link_libraries(Radio PRIVATE Qt6::Quick)

set_target_properties(Radio PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
