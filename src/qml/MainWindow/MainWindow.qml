import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Player

ApplicationWindow {
    id: applicationWindow

    property alias enabled: layout.enabled

    minimumHeight: 560
    minimumWidth: 640
    title: qsTr("Radio")
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
        function onMessageDialogRequested(title, message, exitOnClose) {
            var component = Qt.createComponent("Radio.Shared", "MessageDialog", Component.PreferSynchronous, applicationWindow);

            if (component.status !== Component.Ready) {
                return;
            }

            var dialog = component.createObject(applicationWindow, {
                title: title,
                message: message,
                exitOnClose: exitOnClose
            });

            dialog.open();

            applicationWindow.show();
            applicationWindow.requestActivate();
        }

        target: Player
    }

    ApplicationLayout {
        id: layout

    }
}
