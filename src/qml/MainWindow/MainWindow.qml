import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Radio.ApplicationStyle
import Radio.Shared

ApplicationWindow {
    property alias enabled: layout.enabled

    minimumHeight: 560
    minimumWidth: 640
    title: qsTr("Radio")
    visible: true

    // TODO: make use of this
    footer: Control {
        contentItem: ColumnLayout {
            spacing: 0

            Separator {
                Layout.fillWidth: true
            }

            ImportantLabel {
                Layout.fillWidth: true
                padding: StyleProperties.controls_padding
                text: "**PLACEHOLDER**: Status bar placeholder text"
                textFormat: Label.MarkdownText
            }
        }
    }
    menuBar: MenuBar {
        // TODO
        Menu {
            title: qsTr("&Media")

            Action {
                text: qsTr("&Open Stream...")
            }

            Action {
                text: qsTr("Open Location from &Clipboard")
            }

            MenuSeparator {
            }

            Action {
                text: qsTr("&Quit")
            }
        }

        // TODO
        Menu {
            title: qsTr("&Playback")

            Action {
                text: qsTr("&Play") // qsTr("&Stop") if playing or loading
            }
        }

        // TODO
        Menu {
            title: qsTr("&Audio")

            Action {
                text: qsTr("&Increase Volume") // disabled if at 100
            }

            Action {
                text: qsTr("&Decrease Volume") // disabled if at 0
            }

            Action {
                text: qsTr("&Mute") // qsTr("&Unmute") if muted
            }
        }

        // TODO
        Menu {
            title: qsTr("&Tools")

            Action {
                text: qsTr("&Preferences")
            }
        }
    }

    ColumnLayout {
        id: layout

        anchors {
            fill: parent
            margins: StyleProperties.controls_margins
        }

        TopLayout {
            Layout.fillWidth: true
        }

        BottomLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
