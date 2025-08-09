import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Player

IconButton {
    property Menu menu: null

    ToolTip.text: (checked) ? qsTr("Unmute") : qsTr("Mute")
    ToolTip.visible: hovered || visualFocus
    checked: Player.muted
    icon.source: (checked) ? "qrc:/zet0x0.github.io/icons/speaker-x.svg" : "qrc:/zet0x0.github.io/icons/speaker.svg"

    onClicked: {
        Player.setMuted(!checked);

        if (!!menu) {
            menu.dismiss();
        }
    }
}
