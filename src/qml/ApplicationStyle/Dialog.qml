import QtQuick
import QtQuick.Templates as T
import Radio.Shared

T.Dialog {
    id: control

    horizontalPadding: StyleProperties.controls_padding + StyleProperties.border_width
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding + ((implicitHeaderHeight > 0) ? implicitHeaderHeight + spacing : 0) + ((implicitFooterHeight > 0) ? implicitFooterHeight + spacing : 0))
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding, implicitHeaderWidth, implicitFooterWidth)
    margins: StyleProperties.controls_margins
    spacing: StyleProperties.controls_separator_size
    verticalPadding: StyleProperties.controls_padding

    T.Overlay.modal: Rectangle {
        color: StyleProperties.palette_dialog_modal
    }
    T.Overlay.modeless: Rectangle {
        color: StyleProperties.palette_dialog_modeless
    }
    background: Rectangle {
        color: StyleProperties.palette_background

        border {
            color: StyleProperties.palette_accent
            width: StyleProperties.border_width
        }

        Separator {
            visible: control.header.visible
            width: control.availableWidth
            x: control.leftPadding
            y: control.header?.height
        }

        Separator {
            visible: control.footer.visible
            width: control.availableWidth
            x: control.leftPadding
            y: control.footer?.y - control.spacing
        }
    }
    footer: DialogButtonBox {
        visible: count > 0
    }
    header: Control {
        bottomPadding: StyleProperties.controls_padding
        padding: StyleProperties.controls_padding + StyleProperties.border_width
        visible: parent?.parent === T.Overlay.overlay && control.title

        contentItem: Label {
            elide: Label.ElideRight
            font: StyleProperties.fonts_dialog_titleLabel
            horizontalAlignment: Qt.AlignHCenter
            text: control.title
        }
    }
}
