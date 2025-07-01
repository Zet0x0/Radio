import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts
import Radio.Shared

T.Dialog {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding + ((implicitHeaderHeight > 0) ? implicitHeaderHeight + spacing : 0) + ((implicitFooterHeight > 0) ? implicitFooterHeight + spacing : 0))
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding, implicitHeaderWidth, implicitFooterWidth)
    margins: StyleProperties.controls_margins
    padding: StyleProperties.controls_padding + StyleProperties.border_width
    verticalPadding: StyleProperties.controls_spacing

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
    }
    footer: Control {
        padding: StyleProperties.controls_padding + StyleProperties.border_width
        topPadding: 0

        contentItem: ColumnLayout {
            spacing: StyleProperties.controls_spacing

            Separator {
                Layout.fillWidth: true
            }

            DialogButtonBox {
                Layout.fillWidth: true
                standardButtons: control.standardButtons
                visible: count > 0

                onAccepted: {
                    control.accept();
                }
                onApplied: {
                    control.applied();
                }
                onDiscarded: {
                    control.discarded();
                }
                onHelpRequested: {
                    control.helpRequested();
                }
                onRejected: {
                    control.reject();
                }
                onReset: {
                    control.reset();
                }
            }
        }
    }
    header: Control {
        bottomPadding: 0
        padding: StyleProperties.controls_padding + StyleProperties.border_width
        visible: !!control.title

        contentItem: ColumnLayout {
            spacing: StyleProperties.controls_spacing

            Label {
                Layout.fillWidth: true
                elide: Label.ElideRight
                font: StyleProperties.fonts_dialog_titleLabel
                horizontalAlignment: Qt.AlignHCenter
                text: control.title
            }

            Separator {
                Layout.fillWidth: true
            }
        }
    }
}
