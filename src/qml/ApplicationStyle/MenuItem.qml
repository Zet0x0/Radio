import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.MenuItem {
    id: control

    bottomInset: 0
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, implicitIndicatorHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding, implicitIndicatorWidth + topPadding + bottomPadding)
    leftInset: 0
    padding: StyleProperties.controls_padding + StyleProperties.border_width
    rightInset: 0
    spacing: StyleProperties.controls_spacing
    topInset: 0

    // NOTE: MenuItem gets all blurry if source is not an empty string, Qt bug!
    arrow: ColorImage {
        color: (control.enabled) ? ((control.checked || control.down) ? StyleProperties.palette_accent_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_accent_lighter : StyleProperties.palette_accent)) : StyleProperties.palette_accent_darker
        mirror: control.mirrored
        source: (!control.subMenu) ? "" : "qrc:/zet0x0.github.io/icons/chevron-right.svg"
        visible: !!control.subMenu
        x: (control.mirrored) ? control.leftPadding : control.width - width - control.rightPadding
        y: control.topPadding + Math.floor((control.availableHeight - height) / 2)

        sourceSize {
            height: StyleProperties.controls_menuItem_iconSize
            width: StyleProperties.controls_menuItem_iconSize
        }
    }
    background: Rectangle {
        color: (control.enabled) ? ((control.checked || control.down) ? StyleProperties.palette_accent : ((control.visualFocus || control.hovered) ? StyleProperties.palette_activeFocusBackground : StyleProperties.palette_background)) : StyleProperties.palette_background
        visible: control.down || control.checked || (control.hovered && control.enabled) || control.visualFocus

        border {
            color: (control.enabled) ? (((control.hovered && (control.checked || control.down)) || control.visualFocus) ? StyleProperties.palette_accent_active : StyleProperties.palette_accent) : StyleProperties.palette_accent_darker
            width: StyleProperties.border_width
        }
    }
    contentItem: IconLabel {
        readonly property real arrowPadding: (control.subMenu && control.arrow) ? control.arrow.width + control.spacing : 0
        readonly property real indicatorPadding: (control.checkable && control.indicator) ? control.indicator.width + control.spacing : 0

        alignment: Qt.AlignLeft
        color: (control.enabled) ? ((control.checked || control.down) ? StyleProperties.palette_text_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_text_lighter : StyleProperties.palette_text)) : StyleProperties.palette_text_darker
        display: control.display
        font: control.font
        icon: control.icon
        leftPadding: (control.mirrored) ? arrowPadding : indicatorPadding
        mirrored: control.mirrored
        rightPadding: (control.mirrored) ? indicatorPadding : arrowPadding
        spacing: control.spacing
        text: control.text
    }
    // NOTE: MenuItem gets all blurry if source is not an empty string, Qt bug!
    indicator: ColorImage {
        color: (control.enabled) ? ((control.checked || control.down) ? StyleProperties.palette_accent_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_accent_lighter : StyleProperties.palette_accent)) : StyleProperties.palette_accent_darker
        source: (control.checkable) ? ((control.checked) ? "qrc:/zet0x0.github.io/icons/check.svg" : "qrc:/zet0x0.github.io/icons/x.svg") : ""
        visible: control.checkable
        x: (control.mirrored) ? control.width - width - control.rightPadding : control.leftPadding
        y: control.topPadding + Math.floor((control.availableHeight - height) / 2)

        sourceSize {
            height: StyleProperties.controls_menuItem_iconSize
            width: StyleProperties.controls_menuItem_iconSize
        }
    }

    icon {
        color: (control.enabled) ? ((control.checked || control.down) ? StyleProperties.palette_accent_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_accent_lighter : StyleProperties.palette_accent)) : StyleProperties.palette_accent_darker
        height: StyleProperties.controls_menuItem_iconSize
        width: StyleProperties.controls_menuItem_iconSize
    }
}
