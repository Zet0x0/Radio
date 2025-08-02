import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Player
import Radio.Cpp.Utilities
import Radio.Shared

ApplicationWindow {
    id: applicationWindow

    property alias enabled: layout.enabled

    minimumHeight: 560
    minimumWidth: 640
    title: (Player.state === Player.PLAYING && !!Player.nowPlaying) ? qsTr("%0 - Radio").arg(Player.nowPlaying) : qsTr("Radio")
    visible: true

    footer: ApplicationFooter {
    }
    menuBar: ApplicationMenuBar {
        mainLayoutEnabled: applicationWindow.enabled
    }

    Component.onCompleted: {
        Player.initialize();
    }

    Connections {
        function onAboutDialogRequested() {
            aboutDialog.open();
        }

        function onMessageDialogRequested(title, message, quitOnClose) {
            var component = Qt.createComponent("Radio.Shared", "MessageDialog", Component.PreferSynchronous, applicationWindow);

            if (component.status !== Component.Ready) {
                return;
            }

            var dialog = component.createObject(applicationWindow, {
                title: title,
                message: message,
                quitOnClose: quitOnClose
            });

            dialog.open();

            applicationWindow.requestActivate();
        }

        // TODO
        function onMessagesDialogRequested() {
            console.warn("messages dialog requested, but that doesn't exist, yet...");
        }

        function onOpenLocationDialogRequested(pasteFromClipboard) {
            openLocationDialog.clear();

            if (pasteFromClipboard) {
                openLocationDialog.paste();
            }

            openLocationDialog.open();
        }

        // TODO
        function onSettingsDialogRequested() {
            console.warn("settings dialog requested, but that doesn't exist, yet...");
        }

        target: DialogController
    }

    AboutDialog {
        id: aboutDialog

    }

    OpenLocationDialog {
        id: openLocationDialog

    }

    ApplicationLayout {
        id: layout

    }
}
