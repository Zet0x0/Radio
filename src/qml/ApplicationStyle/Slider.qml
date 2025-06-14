import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.Slider {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitHandleHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitHandleWidth + leftPadding + rightPadding)
    padding: StyleProperties.controls_slider_padding

    background: Rectangle {
        color: StyleProperties.palette_darkerAccent
        height: (control.horizontal) ? implicitHeight : control.availableHeight
        implicitHeight: (control.horizontal) ? StyleProperties.controls_slider_horizontalSwapImplicitHeight : StyleProperties.controls_slider_horizontalSwapImplicitWidth
        implicitWidth: (control.horizontal) ? StyleProperties.controls_slider_horizontalSwapImplicitWidth : StyleProperties.controls_slider_horizontalSwapImplicitHeight
        width: (control.horizontal) ? control.availableWidth : implicitWidth
        x: control.leftPadding + ((control.horizontal) ? 0 : (control.availableWidth - width) / 2)
        y: control.topPadding + ((control.horizontal) ? (control.availableHeight - height) / 2 : 0)

        Rectangle {
            color: (control.enabled) ? StyleProperties.palette_accent : StyleProperties.palette_darkerAccent
            height: (control.horizontal) ? StyleProperties.controls_slider_horizontalSwapImplicitHeight : control.position * parent.height
            width: (control.horizontal) ? control.position * parent.width : StyleProperties.controls_slider_horizontalSwapImplicitHeight
            y: control.horizontal ? 0 : control.visualPosition * parent.height
        }
    }
    handle: Rectangle {
        color: {
            if (control.pressed) {
                return StyleProperties.palette_accent;
            } else if (control.enabled && control.hovered || control.visualFocus) {
                return Color.blend(StyleProperties.palette_background, StyleProperties.palette_accent, 0.5);
            }

            return StyleProperties.palette_background;
        }
        implicitHeight: (control.horizontal) ? StyleProperties.controls_slider_horizontalSwapHandleHeight : StyleProperties.controls_slider_horizontalSwapHandleWidth
        implicitWidth: (control.horizontal) ? StyleProperties.controls_slider_horizontalSwapHandleWidth : StyleProperties.controls_slider_horizontalSwapHandleHeight
        x: control.leftPadding + ((control.horizontal) ? control.visualPosition * (control.availableWidth - width) : (control.availableWidth - width) / 2)
        y: control.topPadding + ((control.horizontal) ? (control.availableHeight - height) / 2 : control.visualPosition * (control.availableHeight - height))

        border {
            color: (control.enabled) ? StyleProperties.palette_accent : StyleProperties.palette_darkerAccent
            width: StyleProperties.border_width
        }
    }
}
