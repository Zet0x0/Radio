// https://github.com/Zet0x0/SampleCustomSystemTray

import QtQuick
import Qt.labs.platform as Labs
import QtQuick.Controls

import Radio.Cpp.Utilities

Labs.SystemTrayIcon {
    required property ApplicationWindow applicationWindow
    required property QtObject systemTrayMenu

    icon.source: "qrc:/icons/applicationIconBackground.svg"
    tooltip: qsTr("Radio")
    visible: systemTrayMenu !== null

    onActivated: reason => {
        switch (reason) {
        case Labs.SystemTrayIcon.Context:
            {
                systemTrayMenu.popup(Utilities.getGlobalCursorPos());

                break;
            }
        case Labs.SystemTrayIcon.Trigger:
            {
                if (applicationWindow.visible) {
                    applicationWindow.hide();
                } else {
                    applicationWindow.show();
                    applicationWindow.requestActivate();
                }

                break;
            }
        default:
            {
                return;
            }
        }
    }
}
