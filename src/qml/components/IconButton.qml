import QtQuick

import QtQuick.Controls.Basic as BC
import QtQuick.Controls

BC.Button {
    id: iconButton

    // QTBUG-80344
    readonly property var _image: contentItem.children[0] || null

    property bool forceHoveredEffect: false

    property color iconColor: "#a0f"

    property string toolTip

    background: Rectangle {
        id: iconButtonBackground

        color: (enabled && (iconButton.forceHoveredEffect
                            || iconButton.hovered)) ? "#a0f" : "#000"

        border.color: (enabled) ? "#a0f" : "#550080"
    }

    icon.color: (enabled) ? ((forceHoveredEffect
                              || hovered) ? "#fff" : iconColor) : "#550080"

    padding: 5
    bottomPadding: padding + iconButtonBackground.border.width
    rightPadding: padding + iconButtonBackground.border.width
    leftPadding: padding + iconButtonBackground.border.width
    topPadding: padding + iconButtonBackground.border.width

    implicitHeight: 18 + topPadding + bottomPadding
    implicitWidth: 18 + leftPadding + rightPadding

    display: BC.Button.IconOnly

    // QTBUG-80344
    Connections {
        function onXChanged() {
            _image.x = Math.floor(_image.x)
        }

        function onYChanged() {
            _image.y = Math.floor(_image.y)
        }

        enabled: !!icon.source

        target: _image
    }

    ToolTip {
        visible: iconButton.hovered && !!iconButton.toolTip

        horizontalAlignment: Text.AlignHCenter

        text: iconButton.toolTip
    }
}
