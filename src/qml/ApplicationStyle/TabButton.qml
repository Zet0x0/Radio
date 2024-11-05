import QtQuick

import QtQuick.Templates as T

T.TabButton {
    id: control

    contentItem: Label {
        color: (control.enabled) ? ((control.hovered
                                     || control.checked) ? "#fff" : "#a0f") : "#550080"

        horizontalAlignment: Label.AlignHCenter
        verticalAlignment: Label.AlignVCenter

        text: control.text
    }

    background: Rectangle {
        id: controlBackground

        color: (control.enabled && (control.hovered
                                    || control.checked)) ? "#a0f" : "#000"

        border.color: (control.enabled) ? "#a0f" : "#550080"
    }

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding

    padding: 5 + controlBackground.border.width
}
