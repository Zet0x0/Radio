import QtQuick
import QtQuick.Templates as T

T.Pane {
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    padding: StyleProperties.controls_padding + StyleProperties.border_width

    background: Rectangle {
        color: StyleProperties.palette_background

        border {
            color: (enabled) ? StyleProperties.palette_accent : StyleProperties.palette_accent_darker
            width: StyleProperties.border_width
        }
    }
}
