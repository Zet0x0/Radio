import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.ItemDelegate {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, implicitIndicatorHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    padding: StyleProperties.controls_padding + StyleProperties.border_width
    spacing: StyleProperties.controls_spacing
    width: ListView.view.width

    background: Rectangle {
        color: (control.enabled) ? ((control.checked || control.highlighted || control.down) ? StyleProperties.palette_accent : ((control.visualFocus || control.hovered) ? StyleProperties.palette_activeFocusBackground : StyleProperties.palette_background)) : ((control.highlighted) ? StyleProperties.palette_accent_darker : StyleProperties.palette_background)
        visible: control.down || control.checked || (control.hovered && control.enabled) || control.visualFocus || control.highlighted

        border {
            color: (control.enabled) ? (((control.hovered && (control.highlighted || control.checked || control.down)) || control.visualFocus) ? StyleProperties.palette_accent_active : StyleProperties.palette_accent) : StyleProperties.palette_accent_darker
            width: StyleProperties.border_width
        }
    }
    contentItem: IconLabel {
        alignment: control.display === IconLabel.IconOnly || ((control.display === IconLabel.TextUnderIcon) ? Qt.AlignCenter : Qt.AlignLeft)
        color: (control.enabled) ? ((control.checked || control.highlighted || control.down) ? StyleProperties.palette_text_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_text_lighter : StyleProperties.palette_text)) : ((control.highlighted) ? StyleProperties.palette_text : StyleProperties.palette_text_darker)
        display: control.display
        font: control.font
        icon: control.icon
        mirrored: control.mirrored
        spacing: control.spacing
        text: control.text
    }

    icon {
        color: (control.enabled) ? ((control.checked || control.highlighted || control.down) ? StyleProperties.palette_accent_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_accent_lighter : StyleProperties.palette_accent)) : ((control.highlighted) ? StyleProperties.palette_accent : StyleProperties.palette_accent_darker)
        height: StyleProperties.controls_itemDelegate_iconSize
        width: StyleProperties.controls_itemDelegate_iconSize
    }
}
