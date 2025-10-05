import QtQuick
import Radio.Cpp
import Radio.Cpp.Player
import Radio.ApplicationStyle

ImportantLabel {
    property bool systemTray: false

    enabled: Player.state === Player.PLAYING && !!Player.nowPlaying
    font: StyleProperties.fonts_nowPlayingLabel
    text: (Player.state === Player.PLAYING) ? (Player.nowPlaying || qsTr("No song information available")) : ((systemTray && !NetworkInformation.online) ? qsTr("You are offline") : qsTr("Not playing anything right now"))
    visible: (systemTray && !Player.station.invalid) || !systemTray
}
