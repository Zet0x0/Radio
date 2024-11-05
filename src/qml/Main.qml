import QtQuick

import Qt.labs.platform as Labs
import QtQuick.Controls
import QtQuick.Layouts

import "./dialogs"
import "./components"
import "./"

import Radio.CppUtilities
import Radio.Player

ApplicationWindow {
    id: applicationWindow

    minimumHeight: 600
    minimumWidth: 800
    title: {
        const state = Player.state;
        var stringifiedState;

        switch (state) {
        case Player.OpeningState:
            {
                stringifiedState = "Opening...";

                break;
            }
        case Player.BufferingState:
            {
                stringifiedState = "Buffering...";

                break;
            }
        case Player.PlayingState:
            {
                stringifiedState = "Playing";

                break;
            }
        case Player.PausedState:
            {
                stringifiedState = "Paused";

                break;
            }
        case Player.StoppedState:
            {
                stringifiedState = "Stopped";

                break;
            }
        case Player.EndedState:
            {
                stringifiedState = "Media End Reached";

                break;
            }
        case Player.ErrorState:
            {
                stringifiedState = "Error";

                break;
            }
        case Player.ParsingStreamUrlState:
            {
                stringifiedState = "Parsing Stream URL...";

                break;
            }
        case Player.UndefinedState:
            {
                break;
            }
        default:
            {
                stringifiedState = `Unhandled State (${state})`;

                break;
            }
        }

        return (stringifiedState) ? `${stringifiedState} - Radio` : "Radio";
    }
    visible: true

    menuBar: OptionallyIndicatedLoader {
        active: Player.initialized

        sourceComponent: ApplicationMenuBar {
        }
    }

    onClosing: {
        if (!Player.playing) {
            Qt.quit();
        }
    }

    OptionallyIndicatedLoader {
        active: !Player.initialized
        anchors.fill: parent

        sourceComponent: MessageDialog {
            id: startUpMessageDialog

            details: Player.initializationDetails
            message: Player.initializationState
            title: (Player.initializationFailed) ? "Player Initialization Error" : "Player is Initializing"

            buttons: Button {
                text: "Close & Exit"

                onClicked: startUpMessageDialog.close()
            }

            Component.onCompleted: Player.beginInitialization()
            onClosed: Qt.quit()
        }
    }

    OptionallyIndicatedLoader {
        active: Player.initialized
        showLoadingIndicator: true

        sourceComponent: Item {
            Labs.SystemTrayIcon {
                icon.source: "qrc:/assets/icons/applicationIconBackground.svg"
                tooltip: (Player.playing) ? (Player.nowPlaying || Player.station.title) : applicationWindow.title
                visible: true
            }

            Shortcut {
                context: Qt.ApplicationShortcut
                sequences: [StandardKey.Paste]

                onActivated: {
                    OpenLocationDialog.paste();
                    OpenLocationDialog.selectAll();

                    Qt.callLater(OpenLocationDialog.open);
                }
            }

            Connections {
                function onMessageDialogRequested(title, message, details) {
                    MessageDialog.show(title, message, details);
                }

                target: CppUtilities
            }

            Binding {
                property: "defaultParent"
                target: DialogMaster
                value: applicationWindow.contentItem
            }

            ColumnLayout {
                anchors.fill: parent

                StationInformationLayout {
                    Layout.fillWidth: true
                }

                ControlLayout {
                    Layout.fillWidth: true
                }

                Services {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }

        anchors {
            fill: parent
            margins: 5
        }
    }
}
