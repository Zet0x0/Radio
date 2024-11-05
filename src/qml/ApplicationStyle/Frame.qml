import QtQuick

import QtQuick.Templates as T

T.Frame {
    background: Rectangle {
        id: controlBackground

        border.color: "#a0f"

        color: "#000"
    }

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding

    padding: 5 + controlBackground.border.width
}
