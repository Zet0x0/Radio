import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Radio.ApplicationStyle
import Radio.Shared
import Radio.Cpp.Utilities

ApplicationWindow {
    property alias enabled: layout.enabled

    minimumHeight: 560
    minimumWidth: 640
    title: qsTr("Radio")
    visible: true

    footer: Control {
        contentItem: ColumnLayout {
            spacing: 0

            Separator {
                Layout.fillWidth: true
            }

            ImportantLabel {
                id: footerLabel

                Layout.fillWidth: true
                padding: StyleProperties.controls_padding
                text: qsTr("Something should appear here...")
                textFormat: Label.MarkdownText
            }
        }

        Connections {
            function onLogMessage(formattedLogMessage) {
                footerLabel.text = formattedLogMessage;
            }

            target: Utilities
        }
    }
    menuBar: MenuBar {
        // TODO
        Menu {
            title: qsTr("&Media")

            Action {
                shortcut: "Ctrl+O"
                text: qsTr("&Open Stream...")
            }

            Action {
                shortcut: "Ctrl+V"
                text: qsTr("Open Location from &Clipboard")
            }

            MenuSeparator {
            }

            Action {
                shortcut: "Ctrl+Q"
                text: qsTr("&Quit")
            }
        }

        // TODO
        Menu {
            title: qsTr("&Playback")

            Action {
                shortcut: "Ctrl+P"
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
                shortcut: "Ctrl+M"
                text: qsTr("&Mute") // qsTr("&Unmute") if muted
            }
        }

        // TODO
        Menu {
            title: qsTr("&Tools")

            Action {
                shortcut: "Ctrl+L"
                text: qsTr("&Messages")
            }

            MenuSeparator {
            }

            Action {
                shortcut: "Ctrl+S"
                text: qsTr("&Preferences")
            }
        }

        // TODO
        Menu {
            title: qsTr("&Help")

            Action {
                text: qsTr("&About")
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
