import QtQuick.Controls

MenuBar {
    id: control

    required property bool mpvUnrestricted

    // TODO
    Menu {
        title: qsTr("&Media")

        Action {
            enabled: control.mpvUnrestricted
            shortcut: "Ctrl+O"
            text: qsTr("&Open Stream...")
        }

        Action {
            enabled: control.mpvUnrestricted
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
        enabled: control.mpvUnrestricted
        title: qsTr("&Playback")

        Action {
            shortcut: "Ctrl+P"
            text: qsTr("&Play") // qsTr("&Stop") if playing or loading
        }
    }

    // TODO
    Menu {
        enabled: control.mpvUnrestricted
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
