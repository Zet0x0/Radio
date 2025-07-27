import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Player
import Radio

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
        function onMessageDialogRequested(title, message, exitOnClose) {
            Utilities.showMessageDialog(applicationWindow, title, message, exitOnClose);
        }

        target: Player
    }

    ApplicationLayout {
        id: layout

    }
}
