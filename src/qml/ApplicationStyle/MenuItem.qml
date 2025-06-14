import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T

T.MenuItem {
    id: control

    bottomInset: 0
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding, implicitIndicatorHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    leftInset: 0
    padding: StyleProperties.controls_padding + StyleProperties.border_width
    rightInset: 0
    spacing: StyleProperties.controls_spacing
    topInset: 0

    arrow: ColorImage {
        color: (control.enabled) ? ((control.checked) ? StyleProperties.palette_activeAccent : ((control.down) ? StyleProperties.palette_lighterAccent : StyleProperties.palette_accent)) : StyleProperties.palette_darkerAccent
        mirror: control.mirrored
        source: (!control.subMenu) ? "" : "qrc:/zet0x0.github.io/icons/chevronRight.svg"
        visible: !!control.subMenu
        x: (control.mirrored) ? control.leftPadding : control.width - width - control.rightPadding
        y: control.topPadding + (control.availableHeight - height) / 2
    }
    background: Rectangle {
        color: (control.checked) ? StyleProperties.palette_accent : Color.blend(StyleProperties.palette_background, StyleProperties.palette_accent, (control.down) ? 0.5 : 0.0)
        visible: control.down || control.checked || control.hovered || control.visualFocus

        border {
            color: (control.enabled) ? StyleProperties.palette_accent : StyleProperties.palette_darkerAccent
            width: StyleProperties.border_width
        }
    }
    contentItem: IconLabel {
        readonly property real arrowPadding: (control.subMenu && control.arrow) ? control.arrow.width + control.spacing : 0
        readonly property real indicatorPadding: (control.checkable && control.indicator) ? control.indicator.width + control.spacing : 0

        alignment: Qt.AlignLeft
        color: (control.enabled) ? ((control.checked) ? StyleProperties.palette_activeText : ((control.down) ? StyleProperties.palette_lighterText : StyleProperties.palette_text)) : StyleProperties.palette_darkerText
        display: control.display
        font: control.font
        icon: control.icon
        leftPadding: (control.mirrored) ? arrowPadding : indicatorPadding
        mirrored: control.mirrored
        rightPadding: (control.mirrored) ? indicatorPadding : arrowPadding
        spacing: control.spacing
        text: control.text
    }
    indicator: ColorImage {
        color: (control.enabled) ? ((control.checked) ? StyleProperties.palette_activeAccent : ((control.down) ? StyleProperties.palette_lighterAccent : StyleProperties.palette_accent)) : StyleProperties.palette_darkerAccent
        source: (control.checked) ? "qrc:/zet0x0.github.io/icons/check.svg" : "qrc:/zet0x0.github.io/icons/cross.svg"
        visible: control.checkable
        x: (control.mirrored) ? control.width - width - control.rightPadding : control.leftPadding
        y: control.topPadding + (control.availableHeight - height) / 2
    }

    icon {
        color: (control.enabled) ? ((control.checked) ? StyleProperties.palette_activeAccent : ((control.down) ? StyleProperties.palette_lighterAccent : StyleProperties.palette_accent)) : StyleProperties.palette_darkerAccent
        height: StyleProperties.controls_menuItem_iconSize
        width: StyleProperties.controls_menuItem_iconSize
    }
}
