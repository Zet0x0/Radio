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

FILE(
    GLOB_RECURSE
    lupdate_sources
    src/*/*.qml
)

QT_ADD_LUPDATE(
    SOURCE_TARGETS Radio
    TS_FILES src/i18n/Radio_en_US.ts
    SOURCES ${lupdate_sources}
    LUPDATE_TARGET lupdate
)

QT_ADD_TRANSLATIONS(
    Radio
    TS_FILES src/i18n/Radio_en_US.ts
    LRELEASE_OPTIONS -idbased
)

ADD_SUBDIRECTORY(src)

TARGET_LINK_LIBRARIES(
    Radio
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        libmpv-2
)

SET_TARGET_PROPERTIES(Radio PROPERTIES WIN32_EXECUTABLE ON)
