import QtQuick
import QtQuick.Templates as T

T.Slider {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitHandleHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitHandleWidth + leftPadding + rightPadding)
    padding: StyleProperties.controls_padding

    background: Rectangle {
        color: StyleProperties.palette_accent_darker
        height: (control.horizontal) ? implicitHeight : control.availableHeight
        implicitHeight: (control.horizontal) ? StyleProperties.controls_slider_implicitHeight : StyleProperties.controls_slider_implicitWidth
        implicitWidth: (control.horizontal) ? StyleProperties.controls_slider_implicitWidth : StyleProperties.controls_slider_implicitHeight
        width: (control.horizontal) ? control.availableWidth : implicitWidth
        x: control.leftPadding + ((control.horizontal) ? 0 : (control.availableWidth - width) / 2)
        y: control.topPadding + ((control.horizontal) ? (control.availableHeight - height) / 2 : 0)

        border {
            color: StyleProperties.palette_accent_active
            width: (control.visualFocus) ? StyleProperties.border_width : 0
        }

        Rectangle {
            color: (control.enabled) ? StyleProperties.palette_accent : StyleProperties.palette_accent_darker
            height: (control.horizontal) ? StyleProperties.controls_slider_implicitHeight : control.position * parent.height
            width: (control.horizontal) ? control.position * parent.width : StyleProperties.controls_slider_implicitHeight
            y: control.horizontal ? 0 : control.visualPosition * parent.height

            border {
                color: StyleProperties.palette_accent_active
                width: (control.visualFocus) ? StyleProperties.border_width : 0
            }
        }
    }
    handle: Rectangle {
        color: (control.enabled) ? ((control.pressed) ? StyleProperties.palette_accent : ((control.visualFocus || control.hovered) ? StyleProperties.palette_activeFocusBackground : StyleProperties.palette_background)) : StyleProperties.palette_background
        implicitHeight: (control.horizontal) ? StyleProperties.controls_slider_handleHeight : StyleProperties.controls_slider_handleWidth
        implicitWidth: (control.horizontal) ? StyleProperties.controls_slider_handleWidth : StyleProperties.controls_slider_handleHeight
        x: control.leftPadding + ((control.horizontal) ? control.visualPosition * (control.availableWidth - width) : (control.availableWidth - width) / 2)
        y: control.topPadding + ((control.horizontal) ? (control.availableHeight - height) / 2 : control.visualPosition * (control.availableHeight - height))

        border {
            color: (control.enabled) ? ((control.pressed || control.visualFocus) ? StyleProperties.palette_accent_active : StyleProperties.palette_accent) : StyleProperties.palette_accent_darker
            width: StyleProperties.border_width
        }
    }
}
