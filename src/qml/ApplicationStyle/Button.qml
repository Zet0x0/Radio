import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.Button {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    padding: StyleProperties.controls_padding + StyleProperties.border_width
    spacing: StyleProperties.controls_spacing

    background: Rectangle {
        color: (control.checked) ? StyleProperties.palette_accent : Color.blend((control.highlighted) ? StyleProperties.palette_accent : StyleProperties.palette_background, StyleProperties.palette_accent, (control.down || control.visualFocus) ? 0.5 : 0.0)
        visible: !control.flat || control.down || control.checked || control.highlighted || control.visualFocus

        border {
            color: StyleProperties.palette_accent
            width: StyleProperties.border_width
        }
    }
    contentItem: IconLabel {
        color: (control.checked || control.highlighted) ? StyleProperties.palette_activeText : ((control.visualFocus || control.down) ? Qt.lighter(StyleProperties.palette_text) : StyleProperties.palette_text)
        display: control.display
        font: control.font
        icon: control.icon
        mirrored: control.mirrored
        spacing: control.spacing
        text: control.text
    }

    icon {
        color: (control.checked || control.highlighted) ? StyleProperties.palette_activeAccent : ((control.visualFocus || control.down) ? Qt.lighter(StyleProperties.palette_accent) : StyleProperties.palette_accent)
        height: StyleProperties.controls_button_iconSize
        width: StyleProperties.controls_button_iconSize
    }
}
