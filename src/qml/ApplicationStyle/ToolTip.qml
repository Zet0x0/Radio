import QtQuick
import QtQuick.Templates as T

T.ToolTip {
    id: control

    closePolicy: T.Popup.CloseOnEscape | T.Popup.CloseOnPressOutsideParent | T.Popup.CloseOnReleaseOutsideParent
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    margins: StyleProperties.controls_margins
    padding: StyleProperties.controls_padding + StyleProperties.border_width
    spacing: StyleProperties.controls_spacing
    x: parent ? Math.floor((parent.width - implicitWidth) / 2) : 0
    y: -implicitHeight - spacing

    background: Rectangle {
        color: StyleProperties.palette_background

        border {
            color: StyleProperties.palette_accent
            width: StyleProperties.border_width
        }
    }
    contentItem: Text {
        color: StyleProperties.palette_text
        font: control.font
        text: control.text
        wrapMode: Text.Wrap
    }
}
