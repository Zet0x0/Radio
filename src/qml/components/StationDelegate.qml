import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import Radio.Favorites
import Radio.Player

Frame {
    id: stationDelegateRootItem

    required property var station

    RowLayout {
        anchors.fill: parent

        StationImage {
            imageUrl: stationDelegateRootItem.station.imageUrl

            Layout.fillHeight: true
        }

        Pane {
            Layout.fillHeight: true
            Layout.fillWidth: true

            ColumnLayout {
                anchors.fill: parent

                Label {
                    text: stationDelegateRootItem.station.title

                    contextMenuEnabled: true

                    elide: Label.ElideRight

                    font.bold: true

                    Layout.fillWidth: true
                }

                Label {
                    text: stationDelegateRootItem.station.subtitle

                    contextMenuEnabled: true

                    elide: Label.ElideRight

                    color: "#550080"

                    visible: !!text

                    Layout.fillWidth: true
                }
            }
        }

        GridLayout {
            columns: 2
            rows: 2

            Layout.fillHeight: true

            IconButton {
                property bool ourStationPlaying: Player.playing
                                                 && (Player.station
                                                     === stationDelegateRootItem.station)

                icon.source: `qrc:/assets/icons/${(ourStationPlaying) ? "stop" : "play"}Icon.svg`

                enabled: stationDelegateRootItem.station.streamUrls.length !== 0

                toolTip: (ourStationPlaying) ? "Stop" : "Play"

                onClicked: {
                    if (ourStationPlaying) {
                        Player.stop()

                        return
                    }

                    const station = stationDelegateRootItem.station

                    if (Player.station != station) {
                        Player.setStation(station)
                    }

                    Player.play()
                }

                Layout.fillHeight: true

                Layout.rowSpan: 2
            }

            FavoriteStationButton {
                station: stationDelegateRootItem.station
            }

            CopyStationStreamUrlButton {
                station: stationDelegateRootItem.station
            }
        }
    }
}
