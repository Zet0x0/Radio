import QtQuick

import QtQuick.Controls

import Radio.Clipboard
import Radio.Player

IconButton {
    id: copyStationStreamUrlButton

    required property var station

    icon.source: "qrc:/assets/icons/copyStreamUrlIcon.svg"

    enabled: station.streamUrls.length !== 0

    toolTip: "Copy Stream URL"

    onClicked: {
        const stationStreamUrls = station.streamUrls

        if (stationStreamUrls.length === 1) {
            Clipboard.setText(Player.getCurrentStreamUrl())

            return
        }

        streamUrlsMenuLoader.item.popup()
    }

    Loader {
        id: streamUrlsMenuLoader

        sourceComponent: Menu {
            Repeater {
                model: copyStationStreamUrlButton.station.streamUrls

                MenuItem {
                    required property var modelData

                    required property int index

                    property bool modelDataSameAsPlayers: modelData === Player.station.streamUrls[Player.streamUrlIndex]

                    text: `Stream URL #${index
                          + 1}${(modelDataSameAsPlayers) ? " [ CURRENT ]" : ""}`

                    font.bold: modelDataSameAsPlayers

                    onTriggered: Clipboard.setText(
                                     (modelDataSameAsPlayers) ? Player.getCurrentStreamUrl(
                                                                    ) : modelData)

                    onHoveredChanged: {
                        if (!hovered) {
                            return
                        }

                        ToolTip.text = (modelDataSameAsPlayers) ? Player.getCurrentStreamUrl(
                                                                      ) : modelData
                    }

                    ToolTip.visible: hovered
                }
            }
        }

        active: copyStationStreamUrlButton.station.streamUrls.length !== 0
    }
}
