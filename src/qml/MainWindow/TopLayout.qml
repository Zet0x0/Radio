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
            source: Player.station.imageUrl || ""

            sourceSize {
                height: height
                width: width
            }

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectCrop
                source: "https://t4.ftcdn.net/jpg/05/43/65/91/360_F_543659162_ujoMeFscPHhs09Qs2lryntvuGN2xqvjY.jpg" // TODO: placeholder icon image here
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

            // other information
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

            // now playing
            Label {
                Layout.fillHeight: true
                Layout.fillWidth: true
                elide: Label.ElideMiddle
                enabled: !Player.station.invalid && !!Player.nowPlaying
                text: (Player.station.invalid) ? qsTr("Nothing to play, browse for stations below") : (Player.nowPlaying || qsTr("No song information available"))
                textFormat: Text.PlainText

                Component.onCompleted: {
                    font.pixelSize *= 1.2;
                }

                font {
                    bold: true
                    italic: !enabled
                }
            }

            // controls
            Row {
                Layout.fillWidth: true
                Layout.preferredHeight: 32
                spacing: 5

                Button {
                    height: parent.height
                    width: height

                    icon {
                        height: height
                        // source: "images/icon.png"
                        width: width
                    }
                }

                Button {
                    height: parent.height
                    width: height

                    icon {
                        height: height
                        // source: "images/icon.png"
                        width: width
                    }
                }

                Button {
                    height: parent.height
                    width: height

                    icon {
                        height: height
                        // source: "images/icon.png"
                        width: width
                    }
                }
            }
        }
    }
}
