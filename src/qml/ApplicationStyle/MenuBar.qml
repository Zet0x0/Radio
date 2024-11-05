import QtQuick

import QtQuick.Templates as T

import "../components"

T.MenuBar {
    id: control

    contentItem: Row {
        spacing: control.spacing

        Repeater {
            model: control.contentModel
        }
    }

    background: Control {
        id: controlBackground

        background: Rectangle {
            color: "#000"
        }

        Divider {
            id: controlBottomLine

            anchors.bottom: parent.bottom

            width: parent.width
        }
    }

    delegate: T.MenuBarItem {
        id: controlDelegate

        contentItem: Label {
            color: (controlDelegate.highlighted
                    && (!controlBackground.hovered
                        || controlDelegate.menu.visible)) ? "#fff" : "#a0f"

            text: controlDelegate.text
        }

        background: Rectangle {
            color: (controlDelegate.highlighted
                    && (!controlBackground.hovered
                        || controlDelegate.menu.visible)) ? "#a0f" : "#000"
        }

        implicitHeight: implicitContentHeight + topPadding + bottomPadding
        implicitWidth: implicitContentWidth + leftPadding + rightPadding

        padding: 5
    }

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding

    padding: 5
    bottomPadding: controlBottomLine.implicitHeight
    topPadding: 0

    spacing: 5
}
