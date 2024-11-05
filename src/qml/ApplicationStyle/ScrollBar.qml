import QtQuick

import QtQuick.Templates as T

T.ScrollBar {
    id: control

    contentItem: Rectangle {
        implicitHeight: (control.horizontal) ? 5 : 10
        implicitWidth: (control.horizontal) ? 10 : 5

        color: "#a0f"
    }

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding

    visible: size !== 1.

    minimumSize: .1
}
