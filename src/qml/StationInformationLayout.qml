import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import "./components"

import Radio.Player

RowLayout {
    StationImage {
        id: stationImage

        imageUrl: NowPlayingImageProvider.currentImageUrl
                  || Player.station.imageUrl

        toolTip: Player.station.subtitle
    }

    Pane {
        implicitHeight: stationImage.height

        Layout.fillWidth: true

        ColumnLayout {
            anchors.fill: parent

            StackLayout {
                id: nowPlayingStackLayout

                visible: !!Player.nowPlaying

                Layout.fillHeight: false
                Layout.fillWidth: true

                Label {
                    contextMenuEnabled: true

                    elide: Label.ElideRight

                    text: Player.nowPlaying

                    font.bold: true

                    MouseArea {
                        anchors.fill: parent

                        onDoubleClicked: nowPlayingStackLayout.currentIndex = 1
                    }
                }

                TextField {
                    background: Item {}

                    placeholderText: "Set a custom value for Now Playing"

                    padding: 0

                    onVisibleChanged: {
                        if (visible) {
                            text = Player.nowPlaying
                        }
                    }

                    onAccepted: {
                        nowPlayingStackLayout.currentIndex = 0

                        Player.setNowPlaying(text)
                    }

                    Keys.onEscapePressed: nowPlayingStackLayout.currentIndex = 0
                }
            }

            RowLayout {
                Layout.fillWidth: true

                Label {
                    font.bold: !nowPlayingStackLayout.visible

                    text: Player.station.title

                    contextMenuEnabled: true

                    elide: Label.ElideRight

                    Layout.fillWidth: true
                }

                Button {
                    background: Item {}

                    text: "..."

                    padding: 0
                }
            }

            Label {
                text: {
                    const elapsed = Player.elapsed

                    return "%0%1:%2 elapsed".arg(
                                (elapsed >= 3600) ? (String(
                                                         Math.trunc(Math.floor(
                                                                        elapsed / 3600))).padStart(
                                                         2, "0") + ":") : "").arg(String(Math.trunc(Math.floor((elapsed % 3600) / 60))).padStart(2, "0")).arg(String(elapsed % 60).padStart(2, "0"))
                }

                visible: Player.state === Player.PlayingState

                elide: Label.ElideRight

                Layout.fillWidth: true
            }
        }
    }
}
