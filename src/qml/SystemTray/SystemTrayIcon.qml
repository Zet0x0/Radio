/* https://github.com/Zet0x0/SampleCustomSystemTray */

import QtQuick
import Qt.labs.platform as Labs

import Radio.Cpp.Utilities
import Radio.Cpp.Player

Labs.SystemTrayIcon {
    required property SystemTrayMenu systemTrayMenu

    icon.source: "qrc:/zet0x0.github.io/icons/applicationIconBackground.svg"
    tooltip: (!Player.station.invalid && !!Player.nowPlaying) ? qsTr("%0 – Radio").arg(Player.nowPlaying) : qsTr("Radio")
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
                systemTrayMenu.showOrHideMainWindow();

                break;
            }
        default:
            {
                return;
            }
        }
    }
}
