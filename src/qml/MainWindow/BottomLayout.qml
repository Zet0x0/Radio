import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Radio.Shared

// TODO: add ComboBox to ApplicationStyle
// TODO: add ItemDelegate to ApplicationStyle
Pane {
    GridLayout {
        anchors.fill: parent
        columns: 4
        rows: 3

        IconButton {
            ToolTip.text: qsTr("Visit the source's site")
            ToolTip.visible: hovered
            icon.source: "qrc:/zet0x0.github.io/icons/external-link.svg"
            implicitHeight: sourceSelect.height

            onClicked: {
                Qt.openUrlExternally(sourceSelect.currentValue);
            }
        }

        ComboBox {
            id: sourceSelect

            ToolTip.text: qsTr("The source to show & search")
            ToolTip.visible: hovered
            model: [
                {
                    name: qsTr("radio.garden"),
                    url: "https://radio.garden"
                }
            ]
            textRole: "name"
            valueRole: "url"
        }

        TextField {
            id: searchField

            Layout.fillWidth: true
            placeholderText: qsTr("Search for any word, country, a specific station, or whatever...")

            onAccepted: {
                searchButton.click();
            }
        }

        // TODO
        Button {
            id: searchButton

            enabled: searchField.length > 0
            text: qsTr("Search")

            onClicked: {
                console.log("station search attempted to be initated");
            }
        }

        Separator {
            Layout.columnSpan: 4
            Layout.fillWidth: true
        }

        // TODO
        Label {
            Layout.columnSpan: 4
            Layout.fillHeight: true
            Layout.fillWidth: true
            text: "Results placeholder"
        }
    }
}
