import QtQuick

import QtQuick.Templates as T

import "../components"

T.ComboBox {
    id: control

    contentItem: TextInput {
        padding: 5 + controlBackground.border.width
        rightPadding: padding - controlBackground.border.width

        color: (enabled) ? "#a0f" : "#550080"

        text: control.displayText

        selectByMouse: false

        readOnly: true

        z: -1
    }

    background: Rectangle {
        id: controlBackground

        border.color: (enabled) ? "#a0f" : "#550080"

        color: "#000"
    }

    indicator: IconButton {
        icon.source: `qrc:/assets/icons/${(control.popup.opened) ? "up" : "down"}ArrowIcon.svg`

        implicitHeight: control.implicitContentHeight
        implicitWidth: control.implicitContentHeight
        x: control.width - width
        z: -1

        forceHoveredEffect: control.hovered
    }

    delegate: ItemDelegate {
        required property var modelData

        width: ListView.view.width

        text: modelData
    }

    popup: Popup {
        contentItem: ScrollView {
            ListView {
                currentIndex: control.highlightedIndex

                boundsBehavior: ListView.StopAtBounds

                model: control.delegateModel

                clip: true
            }
        }

        height: Math.min(implicitContentHeight,
                         192) + topPadding + bottomPadding
        width: control.width
        y: control.height - controlBackground.border.width
    }

    implicitWidth: implicitIndicatorWidth + implicitContentWidth
    implicitHeight: implicitContentHeight

    implicitContentWidthPolicy: T.ComboBox.WidestText
}
