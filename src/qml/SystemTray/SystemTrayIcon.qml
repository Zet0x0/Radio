/* https://github.com/Zet0x0/SampleCustomSystemTray */

import QtQuick
import Qt.labs.platform as Labs

import Radio.Cpp.Utilities
import Radio.MainWindow

Labs.SystemTrayIcon {
    required property MainWindow applicationWindow
    required property SystemTrayMenu systemTrayMenu

    icon.source: "qrc:/zet0x0.github.io/icons/applicationIconBackground.svg"
    tooltip: applicationWindow.title
    visible: true

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
