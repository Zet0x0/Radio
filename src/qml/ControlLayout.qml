import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import "./components"
import "./dialogs"
import "./"

import Radio.Equalizer
import Radio.Favorites
import Radio.Network
import Radio.Player

Pane {
    RowLayout {
        anchors.fill: parent

        FavoriteStationButton {
            station: Player.station
        }

        IconButton {
            icon.source: `qrc:/assets/icons/${(Player.playing) ? "stop" : "play"}Icon.svg`

            enabled: Player.station.streamUrls.length !== 0

            toolTip: (Player.playing) ? "Stop" : "Play"

            onClicked: ((Player.playing) ? Player.stop : Player.play)()
        }

        CopyStationStreamUrlButton {
            station: Player.station
        }

        Control {
            contentItem: Image {
                sourceSize {
                    height: height
                    width: width
                }

                // source: "qrc:/assets/icons/disconnectedIcon.svg"
                source: "qrc:/assets/icons/warningIcon.svg"
            }

            // visible: NetworkInformation.hasInitialized()
            //          && !NetworkInformation.online
            implicitHeight: height
            implicitWidth: height

            ToolTip.text: "Disconnected from Internet"

            ToolTip.visible: hovered

            Layout.fillHeight: true
        }

        Control {
            contentItem: Item {
                LoadingIndicator {
                    toolTipText: {
                        switch (Player.state) {
                        case Player.BufferingState:
                        {
                            return `Buffering... ${Player.bufferProgress}%`
                        }
                        case Player.ParsingStreamUrlState:
                        {
                            return "Parsing Stream URL..."
                        }
                        case Player.OpeningState:
                        {
                            return "Loading..."
                        }
                        default:
                        {
                            return ""
                        }
                        }
                    }

                    anchors.fill: parent

                    z: 1
                }

                Label {
                    visible: Player.state === Player.BufferingState

                    horizontalAlignment: Label.AlignHCenter
                    verticalAlignment: Label.AlignVCenter

                    text: `${Player.bufferProgress}%`

                    anchors.fill: parent
                }
            }

            visible: Player.loading

            implicitWidth: height

            Layout.fillHeight: true
        }

        Item {
            Layout.fillWidth: true
        }

        IconButton {
            toolTip: `Open Equalizer\n[Equalizer ${(Equalizer.enabled) ? "Enabled" : "Disabled"}]`

            iconColor: (Equalizer.enabled) ? "#a0f" : "#550080"
            icon.source: "qrc:/assets/icons/equalizerIcon.svg"

            onClicked: Qt.callLater(EqualizerDialog.open)
        }

        IconButton {
            icon.source: `qrc:/assets/icons/${(Player.muted) ? "mute" : "unmute"}Icon.svg`
            iconColor: (Player.muted) ? "#550080" : "#a0f"

            toolTip: (Player.muted) ? "Unmute" : "Mute"

            onClicked: Player.setMuted(!Player.muted)
        }

        Slider {
            id: volumeSlider

            primaryColor: (Player.muted) ? "#550080" : "#a0f"

            implicitWidth: implicitHeight * 5

            value: Player.volume

            wheelStepSize: 5.
            stepSize: 1.

            from: 0.
            to: 100.

            onMoved: {
                volumeSliderToolTipTimer.restart()
                volumeSliderToolTip.forceVisible = true
            }

            onPressedChanged: volumeSliderToolTipTimer.stopTimer()

            onValueChanged: Player.setVolume(value)

            HoverHandler {
                id: volumeSliderHandleHoverHandler

                parent: volumeSlider.handle

                onHoveredChanged: {
                    if (hovered) {
                        volumeSliderToolTipTimer.stopTimer()
                    }
                }
            }

            Connections {
                function onVolumeChanged(volume) {
                    volumeSlider.value = volume
                }

                target: Player
            }

            ToolTip {
                id: volumeSliderToolTip

                property bool forceVisible: false

                visible: volumeSlider.pressed
                         || volumeSliderHandleHoverHandler.hovered
                         || forceVisible

                text: `Volume: ${volumeSlider.value}%`

                parent: volumeSlider.handle

                Timer {
                    id: volumeSliderToolTipTimer

                    function stopTimer() {
                        stop()

                        volumeSliderToolTip.forceVisible = false
                    }

                    interval: 1000

                    onTriggered: volumeSliderToolTip.forceVisible = false
                }
            }
        }
    }
}
