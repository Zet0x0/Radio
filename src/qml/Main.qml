import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "components/systemTray"
import "components/layouts/mainWindow"

ApplicationWindow {
    id: applicationWindow

    minimumHeight: 480
    minimumWidth: 640
    title: qsTrId("application.name")
    visible: true

    SystemTrayIcon {
        applicationWindow: applicationWindow

        systemTrayMenu: SystemTrayMenu {
        }
    }

    ColumnLayout {
        anchors {
            fill: parent
            margins: 5
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
