import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import "../components"
import "../"

import Radio.CppUtilities
import Radio.Favorites

Pane {
    ColumnLayout {
        anchors.fill: parent

        Label {
            text: {
                const favoriteCount = FavoritesManager.favorites.length

                return (favoriteCount) ? `Favorites (${favoriteCount.toLocaleString(
                                             Qt.locale("en_US"), "f",
                                             0)})` : "Favorites"
            }

            horizontalAlignment: Label.AlignHCenter

            fontSizeMultiplier: 2.

            font.bold: true

            Layout.fillWidth: true
        }

        Label {
            text: "All your Favorites are (supposed to be) present on this page."

            horizontalAlignment: Label.AlignHCenter

            wrapMode: Label.Wrap

            Layout.fillWidth: true
        }

        Divider {
            Layout.fillWidth: true
        }

        StackLayout {
            currentIndex: favoritesListView.count === 0

            Layout.fillHeight: true
            Layout.fillWidth: true

            ScrollView {
                ListView {
                    id: favoritesListView

                    delegate: StationDelegate {
                        required property var modelData

                        station: Utilities.modelDataToStation(modelData)

                        width: ListView.view.width
                    }

                    model: FavoriteStationModel {}

                    boundsBehavior: ListView.StopAtBounds

                    spacing: 5

                    clip: true
                }
            }

            ColumnLayout {
                Item {
                    Layout.fillHeight: true
                }

                Label {
                    horizontalAlignment: Label.AlignHCenter

                    text: "Nothing to show here yet"

                    fontSizeMultiplier: 2.

                    font.bold: true

                    Layout.fillWidth: true
                }

                Label {
                    text: "Click on the \"Add to Favorites\" button to add a station here."

                    horizontalAlignment: Label.AlignHCenter

                    Layout.fillWidth: true
                }

                Item {
                    Layout.fillHeight: true
                }
            }
        }
    }

    RowLayout {
        anchors {
            right: parent.right
            top: parent.top
        }

        IconButton {
            icon.source: "qrc:/assets/icons/synchronizeIcon.svg"

            toolTip: "Synchronize Favorites with File"

            onClicked: FavoritesManager.synchronizeWithFile()
        }

        IconButton {
            icon.source: "qrc:/assets/icons/externalIcon.svg"

            toolTip: "Reveal Favorites File in Explorer"

            onClicked: CppUtilities.executeProgram(
                           "explorer.exe",
                           [`/select,${FavoritesManager.favoritesFilePath()}`])
        }
    }
}
