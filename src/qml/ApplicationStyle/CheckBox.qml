import QtQuick.Templates as T

import "../components"

T.CheckBox {
    id: control

    contentItem: Label {
        leftPadding: control.indicator.width + control.spacing

        verticalAlignment: Label.AlignVCenter

        text: control.text
    }

    indicator: IconButton {
        icon.source: (control.checked) ? "qrc:/assets/icons/checkIcon.svg" : ""

        implicitHeight: control.implicitContentHeight
        implicitWidth: control.implicitContentHeight
        z: -1

        forceHoveredEffect: control.hovered

        padding: 1
    }

    implicitHeight: implicitContentHeight
    implicitWidth: implicitContentWidth

    spacing: 5
}
