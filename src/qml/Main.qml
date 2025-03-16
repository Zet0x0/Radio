import QtQuick
import QtQuick.Controls
import "qrc:/qml/components/systemTray"

ApplicationWindow {
    id: applicationWindow

    property QtObject systemTrayMenu: null

    minimumHeight: 480
    minimumWidth: 640
    title: qsTrId("application.name")
    visible: true

    Component.onCompleted: systemTrayMenu = systemTrayMenuComponent.createObject()

    SystemTrayIcon {
        applicationWindow: applicationWindow
        systemTrayMenu: applicationWindow.systemTrayMenu
    }

    Component {
        id: systemTrayMenuComponent

        SystemTrayMenu {
        }
    }
}
