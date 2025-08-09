import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Player

IconButton {
    property bool systemTray: false
    property Menu systemTrayMenu: null

    ToolTip.text: (checked) ? qsTr("Stop") : qsTr("Play")
    ToolTip.visible: hovered || visualFocus
    checked: Player.state !== Player.STOPPED
    enabled: !!Player.station.streamUrl
    icon.source: (checked) ? "qrc:/zet0x0.github.io/icons/player-stop.svg" : "/zet0x0.github.io/icons/player-play.svg"

    onClicked: {
        if (checked) {
            Player.stop();
        } else {
            Player.play();
        }

        if (systemTray && !!systemTrayMenu) {
            systemTrayMenu.dismiss();
        }
    }
}
