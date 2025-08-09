import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Radio
import Radio.Cpp.Player
import Radio.ApplicationStyle
import Radio.Shared

Control {
    contentItem: RowLayout {
        StationImage {
        }

        ColumnLayout {
            id: rightLayout

            Layout.fillHeight: true
            Layout.fillWidth: true

            Row {
                Layout.fillWidth: true
                spacing: StyleProperties.controls_spacing

                ImportantLabel {
                    id: stationNameLabel

                    text: (Player.station.invalid) ? qsTr("No station selected") : (Player.station.name || qsTr("Unnamed Station"))
                    width: Math.min(parent.width - ((elapsedLabel.visible) ? elapsedLabel.width + parent.spacing : 0), implicitWidth)
                }

                Label {
                    id: elapsedLabel

                    anchors.baseline: stationNameLabel.baseline
                    enabled: false
                    font: StyleProperties.fonts_elapsedLabel
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
                Layout.fillWidth: true

                NowPlayingLabel {
                    width: Math.min(parent.width, implicitWidth)
                    y: Math.floor((parent.height - height) / 2) - rightLayout.spacing
                }
            }

            Control {
                Layout.fillWidth: true

                contentItem: RowLayout {
                    implicitHeight: StyleProperties.controls_topLayout_controlLayout_height

                    ShazamNowPlayingButton {
                        Layout.fillHeight: true
                    }

                    PlayButton {
                        Layout.fillHeight: true
                    }

                    Item {
                        Layout.fillWidth: true
                    }

                    MuteButton {
                        Layout.fillHeight: true
                    }

                    VolumeSlider {
                        Layout.fillHeight: true
                    }
                }
            }
        }
    }
}
