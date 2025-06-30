import QtQuick
import QtQuick.Controls
import Radio.Cpp.Player

MenuBar {
    id: control

    required property bool mainLayoutEnabled

    Menu {
        title: qsTr("&Media")

        // TODO
        Action {
            enabled: control.mainLayoutEnabled
            shortcut: "Ctrl+O"
            text: qsTr("&Open Location...")
        }

        // TODO
        Action {
            enabled: control.mainLayoutEnabled
            shortcut: "Ctrl+V"
            text: qsTr("Open Location from &Clipboard")
        }

        MenuSeparator {
        }

        Action {
            shortcut: "Ctrl+Q"
            text: qsTr("&Quit")

            onTriggered: {
                Qt.quit();
            }
        }
    }

    Menu {
        enabled: control.mainLayoutEnabled
        title: qsTr("&Playback")

        Action {
            shortcut: "Ctrl+P"
            text: (Player.state === Player.STOPPED) ? qsTr("&Play") : qsTr("&Stop")

            onTriggered: {
                if (Player.state === Player.STOPPED) {
                    Player.play();
                } else {
                    Player.stop();
                }
            }
        }
    }

    // TODO
    Menu {
        enabled: control.mainLayoutEnabled
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
