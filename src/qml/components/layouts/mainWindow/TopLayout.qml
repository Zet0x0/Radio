import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "/qml/utilities.js" as Utilities

Control {
    contentItem: RowLayout {
        Image {
            id: stationImage

            Layout.preferredHeight: 96
            Layout.preferredWidth: height
            cache: false
            fillMode: Image.PreserveAspectCrop
            source: test_props.stationImageUrl || ""

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
                    text: test_props.stationName
                    textFormat: Text.PlainText
                    width: Math.min(informationalRow.width - elapsedLabel.width - informationalRow.spacing, implicitWidth)
                }

                Label {
                    id: elapsedLabel

                    enabled: false
                    text: {
                        const total = test_props.elapsed;

                        const seconds = total % 60;
                        const minutes = Math.floor(total / 60) % 60;
                        const hours = Math.floor(total / 3600);

                        var formatted_string = "";

                        if (hours > 0) {
                            formatted_string += Utilities.zero_pad(hours) + ":";
                        }

                        formatted_string += Utilities.zero_pad(minutes) + ":" + Utilities.zero_pad(seconds);

                        return formatted_string + " elapsed";
                    }
                }
            }

            // now playing
            Label {
                Layout.fillHeight: true
                Layout.fillWidth: true
                elide: Label.ElideMiddle
                enabled: !!test_props.nowPlaying
                text: test_props.nowPlaying || "No song information available"
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

    // TODO: once we get a real controller for all the info, we get rid of this altogether
    QtObject {
        id: test_props

        readonly property int elapsed: 3612
        readonly property string nowPlaying: "Humpty Dumpty - Shotgun Willy, Billy Marchiafava"
        // readonly property string nowPlaying: "Humpty Dumpty - Shotgun Willy, Billy Marchiafava Humpty Dumpty - Shotgun Willy, Billy Marchiafava Humpty Dumpty - Shotgun Willy, Billy Marchiafava Humpty Dumpty - Shotgun Willy, Billy Marchiafava Humpty Dumpty - Shotgun Willy, Billy Marchiafava"
        // readonly property string nowPlaying: ""
        // readonly property string stationImageUrl: ""
        readonly property string stationImageUrl: "https://cdn.explorecams.com/storage/photos/LEFEikw0MR_1600.jpg"
        // readonly property string stationName: "NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+NRJ+"
        readonly property string stationName: "NRJ+"
    }
}
