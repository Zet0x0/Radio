import QtQuick
import QtQuick.Controls
import Radio.Cpp.Player
import Radio.Cpp.Utilities

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
            enabled: control.mainLayoutEnabled && !Player.station.invalid
            shortcut: "Ctrl+C"
            text: qsTr("Copy Stream &URL to Clipboard")

            onTriggered: {
                Utilities.copyToClipboard(Player.station.streamUrl);
            }
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
            enabled: Player.state === Player.STOPPED
            shortcut: "Ctrl+P"
            text: qsTr("&Play")

            onTriggered: {
                Player.play();
            }
        }

        Action {
            enabled: Player.state !== Player.STOPPED
            shortcut: "Ctrl+P"
            text: qsTr("&Stop")

            onTriggered: {
                Player.stop();
            }
        }
    }

    Menu {
        enabled: control.mainLayoutEnabled
        title: qsTr("&Audio")

        Action {
            enabled: Player.volume !== 100
            text: qsTr("&Increase Volume")

            onTriggered: {
                Player.setVolume(Math.min(Player.volume + 5, 100));
            }
        }

        Action {
            enabled: Player.volume !== 0
            text: qsTr("&Decrease Volume")

            onTriggered: {
                Player.setVolume(Math.max(Player.volume - 5, 0));
            }
        }

        Action {
            enabled: !Player.muted
            shortcut: "Ctrl+M"
            text: qsTr("&Mute")

            onTriggered: {
                Player.setMuted(true);
            }
        }

        Action {
            enabled: Player.muted
            shortcut: "Ctrl+M"
            text: qsTr("&Unmute")

            onTriggered: {
                Player.setMuted(false);
            }
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
