import QtQuick

import QtQuick.Controls

import "./dialogs"
import "./"

import Radio.Favorites
import Radio.Player

MenuBar {
    Menu {
        title: "File"

        Action {
            text: "Open Location..."

            onTriggered: Qt.callLater(OpenLocationDialog.open)
        }

        MenuSeparator {}

        Action {
            property bool favorited: FavoritesManager.favorites.includes(
                                         Player.station)

            text: (favorited) ? "Remove from Favorites" : "Add to Favorites"

            enabled: Player.station.streamUrls.length !== 0

            onTriggered: ((favorited) ? FavoritesManager.removeStation : FavoritesManager.addStation)(
                             Player.station)
        }

        Action {
            enabled: Player.station.streamUrls.length !== 0

            text: "Copy Stream URL"

            onTriggered: Utilities.copyCurrentStreamUrl()
        }

        MenuSeparator {}

        Action {
            text: "Quit"

            onTriggered: Qt.quit()
        }
    }

    Menu {
        title: "Playback"

        Action {
            enabled: Player.station.streamUrls.length !== 0

            text: (Player.playing) ? "Stop" : "Play"

            onTriggered: ((Player.playing) ? Player.stop : Player.play)()
        }
    }

    Menu {
        title: "Audio"

        Action {
            enabled: Player.volume !== 100

            text: "Increase Volume"

            onTriggered: Player.setVolume(Math.max(0,
                                                   Math.min(Player.volume + 5,
                                                            100)))
        }

        Action {
            enabled: Player.volume !== 0

            text: "Decrease Volume"

            onTriggered: Player.setVolume(Math.max(0,
                                                   Math.min(Player.volume - 5,
                                                            100)))
        }

        Action {
            text: (Player.muted || Player.volume === 0) ? "Unmute" : "Mute"

            enabled: Player.volume !== 0

            onTriggered: Player.setMuted(!Player.muted)
        }
    }

    Menu {
        title: "Tools"

        Action {
            text: "Equalizer"

            onTriggered: Qt.callLater(EqualizerDialog.open)
        }

        Action {
            text: "Media Information"

            onTriggered: Qt.callLater(MediaInformationDialog.open)
        }

        Action {
            text: "Messages"

            onTriggered: Qt.callLater(MessagesDialog.open)
        }

        MenuSeparator {}

        Action {
            text: "Preferences"

            onTriggered: Qt.callLater(PreferencesDialog.open)
        }
    }

    Menu {
        title: "Help"

        Action {
            text: "About"

            onTriggered: Qt.callLater(AboutDialog.open)
        }
    }
}
