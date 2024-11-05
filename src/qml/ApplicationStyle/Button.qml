import QtQuick

import QtQuick.Templates as T

T.Button {
    id: control

    contentItem: Label {
        color: (enabled) ? ((control.hovered
                             || control.checked) ? "#fff" : "#a0f") : "#550080"

        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter

        text: control.text
    }

    background: Rectangle {
        id: controlBackground

        color: (enabled && (control.hovered
                            || control.checked)) ? "#a0f" : "#000"

        border.color: (enabled) ? "#a0f" : "#550080"
    }

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding

    padding: 5 + controlBackground.border.width
}
