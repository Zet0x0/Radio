import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Radio
import Radio.Cpp.Player
import Radio.ApplicationStyle

Control {
    contentItem: RowLayout {
        Image {
            id: stationImage

            Layout.preferredHeight: 96
            Layout.preferredWidth: 96
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

            Row {
                id: informationalRow

                Layout.fillWidth: true
                spacing: StyleProperties.controls_spacing

                Label {
                    id: stationNameLabel

                    elide: Label.ElideMiddle
                    text: (Player.station.invalid) ? qsTr("No station selected") : (Player.station.name || qsTr("Unnamed Station"))
                    textFormat: Text.PlainText
                    width: Math.min(informationalRow.width - elapsedLabel.width - informationalRow.spacing, implicitWidth)
                }

                Label {
                    id: elapsedLabel

                    anchors.baseline: stationNameLabel.baseline
                    enabled: false
                    font: StyleProperties.fonts_mainWindow_elapsedLabel
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

                        return qsTr("%0", "elapsed").arg(formattedString);
                    }
                    visible: !Player.station.invalid && Player.state === Player.PLAYING
                }
            }

            Item {
                Layout.fillHeight: true
            }

            Label {
                Layout.fillHeight: true
                Layout.fillWidth: true
                elide: Label.ElideMiddle
                enabled: !Player.station.invalid && !!Player.nowPlaying
                font: StyleProperties.fonts_mainWindow_nowPlayingLabel
                text: (Player.station.invalid) ? qsTr("Nothing to play, browse for stations below") : (Player.nowPlaying || qsTr("No song information available"))
                textFormat: Text.PlainText
            }

            Item {
                Layout.fillHeight: true
            }

            RowLayout {
                Layout.fillWidth: true

                Button {
                    Layout.preferredHeight: StyleProperties.controls_iconButton_size
                    Layout.preferredWidth: StyleProperties.controls_iconButton_size
                    ToolTip.text: (checked) ? qsTr("Stop") : qsTr("Play")
                    ToolTip.visible: hovered || visualFocus
                    checked: Player.state === Player.LOADING || Player.state === Player.PLAYING
                    display: Button.IconOnly
                    enabled: !!Player.station.streamUrl
                    icon.source: (checked) ? "qrc:/zet0x0.github.io/icons/stop.svg" : "/zet0x0.github.io/icons/play.svg"

                    onClicked: {
                        if (checked) {
                            Player.stop();
                        } else {
                            Player.play();
                        }
                    }
                }

                Item {
                    Layout.fillWidth: true
                }

                Button {
                    Layout.preferredHeight: StyleProperties.controls_iconButton_size
                    Layout.preferredWidth: StyleProperties.controls_iconButton_size
                    ToolTip.text: (checked) ? qsTr("Unmute") : qsTr("Mute")
                    ToolTip.visible: hovered || visualFocus
                    checked: Player.muted
                    display: Button.IconOnly
                    icon.source: (checked) ? "qrc:/zet0x0.github.io/icons/mute.svg" : "qrc:/zet0x0.github.io/icons/unmute.svg"

                    onClicked: {
                        Player.setMuted(!checked);
                    }
                }

                // TODO: make this its own custom VolumeSlider or something like that to support red color for volume above 100 and tooltip and so on
                Slider {
                    ToolTip.text: qsTr("Volume: %0%").arg(value)
                    ToolTip.visible: hovered || visualFocus || pressed
                    padding: StyleProperties.controls_volumeSlider_padding
                    palette.accent: (Player.muted) ? disabledPalette.accent : activePalette.accent
                    stepSize: 1
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
