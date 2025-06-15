import QtQuick
import QtQuick.Controls
import Radio.Cpp.Player
import Radio.ApplicationStyle

ImportantLabel {
    property bool systemTray: false

    enabled: !Player.station.invalid && !!Player.nowPlaying
    font: StyleProperties.fonts_mainWindow_nowPlayingLabel
    text: (Player.station.invalid) ? qsTr("Nothing to play, browse for stations below") : (Player.nowPlaying || qsTr("No song information available"))
    visible: (systemTray && !Player.station.invalid) || !systemTray
}
