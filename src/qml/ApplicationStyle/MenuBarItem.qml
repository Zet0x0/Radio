import QtQuick
import QtQuick.Templates as T
import QtQuick.Controls.impl

T.MenuBarItem {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, implicitIndicatorHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    padding: StyleProperties.controls_padding + StyleProperties.border_width
    spacing: StyleProperties.controls_spacing
    verticalPadding: StyleProperties.controls_padding

    background: Rectangle {
        color: (control.enabled) ? ((control.checked || control.down || control.highlighted && control.menu.visible) ? StyleProperties.palette_accent : ((control.visualFocus || control.hovered) ? StyleProperties.palette_activeFocusBackground : StyleProperties.palette_background)) : StyleProperties.palette_background
        visible: control.down || control.checked || control.hovered && control.enabled || control.visualFocus || control.highlighted && control.menu.visible

        border {
            color: (control.enabled) ? (((control.hovered && (control.checked || control.down)) || control.visualFocus || control.highlighted && control.menu.visible) ? StyleProperties.palette_accent_active : StyleProperties.palette_accent) : StyleProperties.palette_accent_darker
            width: StyleProperties.border_width
        }

        Rectangle {
            color: (parent as Rectangle).color

            anchors {
                bottom: parent.bottom
                left: parent.left
                leftMargin: StyleProperties.border_width
                right: parent.right
                rightMargin: StyleProperties.border_width
                top: parent.top
            }
        }
    }
    contentItem: IconLabel {
        alignment: Qt.AlignLeft
        color: (control.enabled) ? ((control.checked || control.down || control.highlighted && control.menu.visible) ? StyleProperties.palette_text_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_text_lighter : StyleProperties.palette_text)) : StyleProperties.palette_text_darker
        display: control.display
        font: control.font
        icon: control.icon
        mirrored: control.mirrored
        spacing: control.spacing
        text: control.text
    }

    icon {
        color: (control.enabled) ? ((control.checked || control.down || control.highlighted && control.menu.visible) ? StyleProperties.palette_accent_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_accent_lighter : StyleProperties.palette_accent)) : StyleProperties.palette_accent_darker
        height: StyleProperties.controls_menuBarItem_iconSize
        width: StyleProperties.controls_menuBarItem_iconSize
    }
}
