import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Player

IconButton {
    property bool systemTray: false
    property Menu systemTrayMenu: null

    ToolTip.text: (checked) ? qsTr("Unmute") : qsTr("Mute")
    ToolTip.visible: hovered || visualFocus
    checked: Player.muted
    icon.source: (checked) ? "qrc:/zet0x0.github.io/icons/speaker-x-mark.svg" : "qrc:/zet0x0.github.io/icons/speaker-wave.svg"

    onClicked: {
        Player.setMuted(!checked);

        if (systemTray && !!systemTrayMenu) {
            systemTrayMenu.dismiss();
        }
    }
}
