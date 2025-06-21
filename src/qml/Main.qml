import Radio.MainWindow
import Radio.SystemTray
import Radio.Cpp.Player
import QtQml

MainWindow {
    id: applicationWindow

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
        }

        target: Player
    }

    SystemTrayIcon {
        applicationWindow: applicationWindow

        systemTrayMenu: SystemTrayMenu {
            applicationWindow: applicationWindow
        }
    }
}
