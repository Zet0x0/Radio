import QtQuick

import QtQuick.Templates as T

T.ItemDelegate {
    id: control

    contentItem: Label {
        color: (control.hovered || control.visualFocus) ? "#fff" : "#a0f"

        text: control.text
    }

    background: Rectangle {
        color: (control.hovered || control.visualFocus) ? "#a0f" : "#000"
    }

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding

    padding: 5
}
