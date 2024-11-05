import QtQuick

import QtQuick.Layouts

ColumnLayout {
    id: tabView

    property Component stackLayout

    spacing: -1

    TabBar {}

    Rectangle {
        id: stackLayoutBackground

        border.color: "#a0f"

        color: "#000"

        Layout.fillHeight: true
        Layout.fillWidth: true

        Loader {
            sourceComponent: tabView.stackLayout

            onLoaded: {
                anchors.margins = 5 + stackLayoutBackground.border.width
                anchors.fill = parent

                currentIndex = listView.currentIndex
            }
        }
    }
}
