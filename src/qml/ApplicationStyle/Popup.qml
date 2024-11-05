import QtQuick

import QtQuick.Templates as T

T.Popup {
    background: Rectangle {
        id: controlBackground

        border.color: "#a0f"

        color: "#000"
    }

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding
    y: (parent) ? Math.floor((parent.height - height) / 2) : 0
    x: (parent) ? Math.floor((parent.width - width) / 2) : 0

    padding: 5 + controlBackground.border.width

    focus: true
}
