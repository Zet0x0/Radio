import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Player
import Radio.Cpp

IconButton {
    property Menu menu: null

    ToolTip.text: qsTr("Google Search through Shazam's site what's currently playing")
    ToolTip.visible: hovered || visualFocus
    enabled: Player.state === Player.PLAYING && !!Player.nowPlaying
    icon.source: "qrc:/zet0x0.github.io/icons/brand-shazam.svg"

    onClicked: {
        Qt.openUrlExternally(CppUtilities.getShazamLinkFor(Player.nowPlaying));

        if (!!menu) {
            menu.dismiss();
        }
    }
}
