import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Radio
import Radio.Cpp.Player

Control {
    contentItem: RowLayout {
        Image {
            id: stationImage

            Layout.preferredHeight: 96
            Layout.preferredWidth: height
            cache: false
            fillMode: Image.PreserveAspectCrop
            source: Player.station.imageUrl

            sourceSize {
                height: height
                width: width
            }

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                source: "qrc:/zet0x0.github.io/icons/applicationIcon.svg"
                visible: stationImage.status !== Image.Ready

                sourceSize {
                    height: height
                    width: width
                }
            }
        }

        ColumnLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            /* other information */
            Row {
                id: informationalRow

                Layout.fillWidth: true
                Layout.preferredHeight: implicitHeight
                spacing: 5

                Label {
                    elide: Label.ElideMiddle
                    text: (Player.station.invalid) ? qsTr("No station selected") : (Player.station.name || qsTr("Unnamed Station"))
                    textFormat: Text.PlainText
                    width: Math.min(informationalRow.width - elapsedLabel.width - informationalRow.spacing, implicitWidth)
                }

                Label {
                    id: elapsedLabel

                    enabled: false
                    text: {
                        const total = Player.elapsed;

                        const seconds = total % 60;
                        const minutes = Math.floor(total / 60) % 60;
                        const hours = Math.floor(total / 3600);

                        var formattedString = "";

                        if (hours > 0) {
                            formattedString += Utilities.zeroPad(hours) + ":";
                        }

                        formattedString += Utilities.zeroPad(minutes) + ":" + Utilities.zeroPad(seconds);

                        return qsTr("%0 elapsed").arg(formattedString);
                    }
                    visible: !Player.station.invalid && Player.state === Player.PLAYING
                }
            }

            /* now playing */
            Label {
                Layout.fillHeight: true
                Layout.fillWidth: true
                elide: Label.ElideMiddle
                enabled: !Player.station.invalid && !!Player.nowPlaying
                font.bold: enabled
                text: (Player.station.invalid) ? qsTr("Nothing to play, browse for stations below") : (Player.nowPlaying || qsTr("No song information available"))
                textFormat: Text.PlainText

                Component.onCompleted: {
                    font.pixelSize *= 1.2;
                }
            }

            /* controls */
            // TODO: fix icons being tiny
            // TODO: fix something causing a weird grandgrandparent layout resize
            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 32

                Button {
                    readonly property bool playing: Player.state === Player.LOADING || Player.state === Player.PLAYING

                    Layout.fillHeight: true
                    Layout.preferredWidth: 32
                    ToolTip.text: (playing) ? qsTr("Stop") : qsTr("Play")
                    ToolTip.visible: hovered
                    display: Button.IconOnly
                    enabled: !!Player.station.streamUrl

                    onClicked: {
                        if (playing) {
                            Player.stop();
                        } else {
                            Player.play();
                        }
                    }

                    icon {
                        height: height
                        source: (playing) ? "qrc:/zet0x0.github.io/icons/stop.svg" : "/zet0x0.github.io/icons/play.svg"
                        width: width
                    }
                }

                Item {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                Button {
                    Layout.fillHeight: true
                    Layout.preferredWidth: 32
                    ToolTip.text: (Player.muted) ? qsTr("Unmute") : qsTr("Mute")
                    ToolTip.visible: hovered
                    display: Button.IconOnly

                    onClicked: {
                        Player.setMuted(!Player.muted);
                    }

                    icon {
                        height: height
                        source: (Player.muted) ? "qrc:/zet0x0.github.io/icons/mute.svg" : "qrc:/zet0x0.github.io/icons/unmute.svg"
                        width: width
                    }
                }

                Slider {
                    Layout.fillHeight: true
                    ToolTip.text: qsTr("Volume: %0%").arg(value)
                    ToolTip.visible: hovered
                    from: 0
                    palette.accent: (Player.muted) ? disabledPalette.accent : activePalette.accent
                    stepSize: 1.0
                    to: Player.maxVolume
                    value: Player.volume

                    onMoved: {
                        Player.setVolume(value);
                        Player.setMuted(false);
                    }

                    SystemPalette {
                        id: activePalette

                        colorGroup: SystemPalette.Active
                    }

                    SystemPalette {
                        id: disabledPalette

                        colorGroup: SystemPalette.Disabled
                    }
                }
            }
        }
    }
}
