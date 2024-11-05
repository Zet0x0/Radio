import QtQuick

import QtQuick.Controls

Control {
    property string toolTipText

    contentItem: Image {
        id: loadingIndicatorImage

        sourceSize {
            height: height
            width: width
        }

        source: "qrc:/assets/icons/loadingIcon.svg"

        fillMode: Image.PreserveAspectFit

        antialiasing: true

        RotationAnimation on rotation {
            running: loadingIndicatorImage.visible

            loops: RotationAnimation.Infinite

            duration: 500

            from: 0
            to: 360
        }
    }

    implicitWidth: height

    ToolTip.visible: !!toolTipText && hovered

    ToolTip.text: toolTipText
}
