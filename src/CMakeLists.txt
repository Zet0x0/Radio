cmake_minimum_required(VERSION 3.16)
project(Radio VERSION 1.0.0.0 LANGUAGES CXX)

find_package(Qt6 COMPONENTS Core Gui Network Widgets Quick Qml Concurrent)

set(CMAKE_WIN32_EXECUTABLE TRUE)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

qt_policy(SET QTP0001 NEW)

qt_add_executable(Radio
    assets/assets.qrc
    resources.rc
    qml/qml.qrc

    stationModels/favoriteStationModel.cpp
    stationModels/favoriteStationModel.h
    favoritesManager.cpp
    favoritesManager.h

    networkInformation.cpp
    networkInformation.h

    urlValidator.cpp
    urlValidator.h

    clipboard.cpp
    clipboard.h

    libVlcLogMessageModel.cpp
    libVlcLogMessageModel.h
    player.cpp
    player.h
    nowPlayingImageProvider.h
    nowPlayingImageProvider.cpp
    streamUrlParser.h
    streamUrlParser.cpp

    equalizer.cpp
    equalizer.h

    stationModels/radioGardenServiceStationModel.cpp
    stationModels/radioGardenServiceStationModel.h
    stationModels/radioNetServiceStationModel.cpp
    stationModels/radioNetServiceStationModel.h
    stationModels/zenoFmServiceStationModel.cpp
    stationModels/zenoFmServiceStationModel.h
    stationModels/stationModel.cpp
    stationModels/stationModel.h
    stationModels/serviceStationModel.cpp
    stationModels/serviceStationModel.h

    utilities.cpp
    utilities.h

    station.cpp
    station.h

    discord.cpp
    discord.h

    main.cpp

    networkAccessManager.h
    networkAccessManager.cpp
    TODO.txt
)

set(LIBVLC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/libvlc")

include_directories(${LIBVLC_DIR}/include)

target_link_libraries(Radio
    PRIVATE ${LIBVLC_DIR}/lib/libvlc.lib
            ${LIBVLC_DIR}/lib/libvlccore.lib

            Qt6::Core
            Qt6::Gui
            Qt6::Network
            Qt6::Widgets
            Qt6::Qml
            Qt6::Quick
            Qt6::Concurrent
)
