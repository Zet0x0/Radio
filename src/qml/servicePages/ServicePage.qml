import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import "../components"
import "../dialogs"
import "../"

ColumnLayout {
    id: servicePageRootItem

    property var serviceStationModel

    property string serviceTitle

    Label {
        horizontalAlignment: Label.AlignHCenter

        text: servicePageRootItem.serviceTitle

        fontSizeMultiplier: 2.

        font.bold: true

        Layout.fillWidth: true
    }

    Divider {
        Layout.fillWidth: true
    }

    RowLayout {
        Layout.fillWidth: true

        TextField {
            id: searchTextField

            function search() {
                servicePageRootItem.serviceStationModel.search(text)

                stackLayout.currentIndex = 1
            }

            enabled: !servicePageRootItem.serviceStationModel.searching

            placeholderText: "Search for stations"

            Keys.onPressed: event => {
                                const eventKey = event.key

                                if ((eventKey !== Qt.Key_Return
                                     && eventKey !== Qt.Key_Enter) || !text) {
                                    return
                                }

                                search()
                            }

            Layout.fillWidth: true
        }

        LoadingIndicator {
            visible: servicePageRootItem.serviceStationModel.searching

            implicitHeight: searchTextField.height

            toolTipText: "Searching..."
        }

        Button {
            enabled: !servicePageRootItem.serviceStationModel.searching
                     && !!searchTextField.text

            text: "Search"

            onClicked: searchTextField.search()
        }
    }

    StackLayout {
        id: stackLayout

        Layout.fillHeight: true
        Layout.fillWidth: true

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
                text: "Start by thinking what to search for, then use the text field and the button above."

                horizontalAlignment: Label.AlignHCenter

                wrapMode: Label.Wrap

                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
            }
        }

        Label {
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter

            fontSizeMultiplier: 2.

            text: "Searching..."

            font.bold: true
        }

        ColumnLayout {
            Item {
                Layout.fillHeight: true
            }

            Label {
                horizontalAlignment: Label.AlignHCenter

                fontSizeMultiplier: 2.

                text: "Search Error"

                font.bold: true

                Layout.fillWidth: true
            }

            Label {
                id: errorLabel

                horizontalAlignment: Label.AlignHCenter

                contextMenuEnabled: true

                wrapMode: Label.Wrap

                Layout.fillWidth: true
            }

            Item {
                Layout.fillHeight: true
            }
        }

        Label {
            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter

            text: "No results found"

            fontSizeMultiplier: 2.

            font.bold: true
        }

        ScrollView {
            ListView {
                id: serviceStationModelListView

                delegate: StationDelegate {
                    required property var modelData

                    station: Utilities.modelDataToStation(modelData)

                    width: ListView.view.width
                }

                model: servicePageRootItem.serviceStationModel

                boundsBehavior: ListView.StopAtBounds

                spacing: 5

                clip: true

                Connections {
                    function onErrorOccurred(error) {
                        if (serviceStationModelListView.count !== 0) {
                            MessageDialog.show(
                                        `${servicePageRootItem.serviceTitle} Search Error`,
                                        error, "")
                            return
                        }

                        errorLabel.text = error

                        stackLayout.currentIndex = 2
                    }

                    function onFinished() {
                        stackLayout.currentIndex = (serviceStationModelListView.count === 0) ? 3 : 4
                    }

                    target: servicePageRootItem.serviceStationModel
                }
            }
        }
    }
}
