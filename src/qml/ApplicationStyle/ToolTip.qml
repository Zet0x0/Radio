import QtQuick

import QtQuick.Templates as T

T.ToolTip {
    id: control

    property alias horizontalAlignment: controlContentItem.horizontalAlignment

    contentItem: Text {
        id: controlContentItem

        textFormat: Text.PlainText

        elide: Text.ElideRight

        wrapMode: Text.Wrap

        text: control.text

        color: "#a0f"
    }

    background: Rectangle {
        id: controlBackground

        border.color: "#a0f"

        color: "#000"
    }

    closePolicy: T.ToolTip.CloseOnEscape | T.ToolTip.CloseOnPressOutsideParent
                 | T.ToolTip.CloseOnReleaseOutsideParent

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding
    x: (parent) ? Math.floor((parent.width - width) / 2) : 0
    y: -implicitHeight - spacing

    padding: 5 + controlBackground.border.width

    margins: 5

    spacing: 5
}
