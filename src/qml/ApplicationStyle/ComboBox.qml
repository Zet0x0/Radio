pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Controls.impl
import QtQuick.Templates as T
import Radio.Shared

T.ComboBox {
    id: control

    implicitContentWidthPolicy: T.ComboBox.WidestText
    implicitHeight: implicitBackgroundHeight + topInset + bottomInset
    implicitWidth: implicitBackgroundWidth + leftInset + rightInset
    padding: 0
    spacing: StyleProperties.controls_separator_size

    background: Rectangle {
        color: (control.enabled) ? ((control.down) ? StyleProperties.palette_accent : ((control.visualFocus || control.hovered) ? StyleProperties.palette_activeFocusBackground : StyleProperties.palette_background)) : StyleProperties.palette_background
        implicitHeight: control.implicitContentHeight
        implicitWidth: control.implicitContentWidth
        visible: (control.flat && control.enabled && control.hovered) || !control.flat || control.down || control.visualFocus

        border {
            color: (control.enabled) ? ((control.down || control.visualFocus) ? StyleProperties.palette_accent_active : StyleProperties.palette_accent) : StyleProperties.palette_accent_darker
            width: StyleProperties.border_width
        }

        Separator {
            color: (parent as Rectangle).border.color
            height: control.height
            horizontal: false
            x: (control.mirrored) ? (control.indicator.width - width) : control.indicator.x
        }
    }
    contentItem: T.TextField {
        autoScroll: false
        color: (control.enabled) ? ((control.down) ? StyleProperties.palette_text_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_text_lighter : StyleProperties.palette_text)) : StyleProperties.palette_text_darker
        enabled: false
        implicitHeight: contentHeight + topPadding + bottomPadding
        implicitWidth: textMetrics.width + leftPadding + rightPadding
        inputMethodHints: control.inputMethodHints
        leftPadding: (control.mirrored) ? (StyleProperties.controls_padding + control.indicator.width) : padding
        padding: StyleProperties.controls_padding + StyleProperties.border_width
        rightPadding: (control.mirrored) ? padding : (StyleProperties.controls_padding + control.indicator.width)
        text: control.displayText
        validator: control.validator
        verticalAlignment: Text.AlignVCenter

        TextMetrics {
            id: textMetrics

            font: control.font
            renderType: (control.contentItem as T.TextField).renderType
            text: control.displayText
        }
    }
    delegate: ItemDelegate {
        required property int index
        required property var model

        font.weight: (highlighted) ? Font.Bold : Font.Normal
        highlighted: control.currentIndex === index
        text: model[control.textRole]
    }
    indicator: Control {
        height: control.height
        leftPadding: (control.mirrored) ? padding : (StyleProperties.controls_separator_size + StyleProperties.controls_comboBox_indicator_padding)
        padding: StyleProperties.border_width + StyleProperties.controls_comboBox_indicator_padding
        rightPadding: (control.mirrored) ? (StyleProperties.controls_separator_size + StyleProperties.controls_comboBox_indicator_padding) : padding
        width: control.height
        x: (control.mirrored) ? 0 : (control.width - width)

        contentItem: ColorImage {
            color: (control.enabled) ? ((control.down) ? StyleProperties.palette_accent_active : ((control.visualFocus || control.hovered) ? StyleProperties.palette_accent_lighter : StyleProperties.palette_accent)) : (StyleProperties.palette_accent_darker)
            source: (control.popup.visible) ? "qrc:/zet0x0.github.io/icons/chevron-up.svg" : "qrc:/zet0x0.github.io/icons/chevron-down.svg"

            sourceSize {
                height: height
                width: width
            }
        }
    }
    popup: T.Popup {
        height: Math.min(contentItem.implicitHeight + topPadding + bottomPadding, control.Window.height - topMargin - bottomMargin, Math.floor((control.Window.height - topMargin - bottomMargin) / 2))
        margins: StyleProperties.controls_margins
        padding: StyleProperties.controls_padding + StyleProperties.border_width
        topPadding: StyleProperties.controls_padding
        width: control.width
        y: control.height

        background: Rectangle {
            color: StyleProperties.palette_background

            border {
                color: StyleProperties.palette_accent
                width: StyleProperties.border_width
            }

            Rectangle {
                color: StyleProperties.palette_background
                height: StyleProperties.border_width
                width: parent.width - StyleProperties.border_width * 2
                x: StyleProperties.border_width
            }
        }
        contentItem: ListView {
            boundsBehavior: ListView.StopAtBounds
            clip: true
            currentIndex: control.highlightedIndex
            highlightMoveDuration: 0
            implicitHeight: contentHeight
            model: control.delegateModel
            spacing: StyleProperties.controls_spacing

            T.ScrollIndicator.vertical: ScrollIndicator {
            }
        }
    }
}
