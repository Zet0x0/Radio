import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Player
import Radio.Cpp.Utilities

IconButton {
    property Menu menu: null

    ToolTip.text: qsTr("Google Search what's currently playing through Shazam's site")
    ToolTip.visible: hovered || visualFocus
    enabled: !Player.station.invalid && !!Player.nowPlaying
    icon.source: "qrc:/zet0x0.github.io/icons/brand-shazam.svg"

    onClicked: {
        Qt.openUrlExternally(Utilities.getShazamLinkFor(Player.nowPlaying));

        if (!!menu) {
            menu.dismiss();
        }
    }
}
