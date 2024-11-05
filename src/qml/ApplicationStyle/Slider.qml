import QtQuick

import QtQuick.Templates as T

T.Slider {
    id: control

    property color secondaryColor: "#550080"
    property color primaryColor: "#a0f"

    property double wheelStepSize: 0.

    background: Rectangle {
        height: (control.horizontal) ? implicitHeight : control.availableHeight
        width: (control.horizontal) ? control.availableWidth : implicitWidth
        y: (control.horizontal) ? ((control.availableHeight - height) / 2) : 0
        x: (control.horizontal) ? 0 : ((control.availableWidth - width) / 2)
        implicitHeight: (control.horizontal) ? 1 : control.height
        implicitWidth: (control.horizontal) ? control.width : 1

        color: (enabled) ? control.secondaryColor : "#550080"

        Rectangle {
            y: (control.horizontal) ? 0 : (control.visualPosition * parent.height)
            height: (control.horizontal) ? 1 : (control.position * parent.height)
            width: (control.horizontal) ? (control.position * parent.width) : 1

            color: (enabled) ? control.primaryColor : "#550080"
        }
    }

    handle: Rectangle {
        y: (control.horizontal) ? ((control.height - height)
                                   / 2) : (control.visualPosition * (control.height - height))
        x: (control.horizontal) ? (control.visualPosition
                                   * (control.width - width)) : ((control.width - width) / 2)
        implicitHeight: (control.horizontal) ? 30 : 10
        implicitWidth: (control.horizontal) ? 10 : 30

        color: (enabled) ? control.primaryColor : "#550080"
    }

    implicitHeight: implicitHandleHeight + topPadding + bottomPadding
    implicitWidth: implicitHandleWidth + leftPadding + rightPadding

    WheelHandler {
        acceptedButtons: Qt.NoButton

        onWheel: event => {
                     const wheelStepSize = control.wheelStepSize
                     const angleDelta = event.angleDelta

                     control.value += (angleDelta.x < 0
                                       || angleDelta.y > 0) ? wheelStepSize : -wheelStepSize

                     control.moved()
                 }
    }
}
