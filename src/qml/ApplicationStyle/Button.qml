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
        color: (control.enabled) ? ((control.checked || control.highlighted || control.down) ? StyleProperties.palette_accent : ((control.visualFocus || control.hovered) ? StyleProperties.palette_activeFocusBackground : StyleProperties.palette_background)) : ((control.highlighted) ? StyleProperties.palette_darkerAccent : StyleProperties.palette_background)
        visible: (control.flat && control.enabled && control.hovered) || !control.flat || control.down || control.checked || control.highlighted || control.visualFocus

        border {
            color: (control.enabled) ? (((control.visualFocus || control.hovered) && (control.checked || control.highlighted || control.down)) ? StyleProperties.palette_activeAccent : StyleProperties.palette_accent) : StyleProperties.palette_darkerAccent
            width: StyleProperties.border_width
        }
    }
    contentItem: IconLabel {
        color: (control.enabled) ? ((control.checked || control.highlighted || control.down) ? StyleProperties.palette_activeText : ((control.visualFocus || control.hovered) ? StyleProperties.palette_lighterText : StyleProperties.palette_text)) : ((control.highlighted) ? StyleProperties.palette_text : StyleProperties.palette_darkerText)
        display: control.display
        font: control.font
        icon: control.icon
        mirrored: control.mirrored
        spacing: control.spacing
        text: control.text
    }

    icon {
        color: (control.enabled) ? ((control.checked || control.highlighted || control.down) ? StyleProperties.palette_activeAccent : ((control.visualFocus || control.hovered) ? StyleProperties.palette_lighterAccent : StyleProperties.palette_accent)) : ((control.highlighted) ? StyleProperties.palette_accent : StyleProperties.palette_darkerAccent)
        height: StyleProperties.controls_button_iconSize
        width: StyleProperties.controls_button_iconSize
    }
}
