import QtQuick

import QtQuick.Templates as T
import QtQuick.Layouts

import "../components"

T.Dialog {
    id: control

    property int buttonAlignment: Qt.AlignHCenter
    property Item buttons

    background: Rectangle {
        id: controlBackground

        border.color: "#a0f"

        color: "#000"
    }

    buttons: Button {
        text: "Close"

        onClicked: control.close()
    }

    footer: Pane {
        padding: control.padding
        topPadding: 0

        ColumnLayout {
            anchors.fill: parent

            Divider {
                Layout.fillWidth: true
            }

            Control {
                contentItem: control.buttons

                Layout.alignment: control.buttonAlignment
            }
        }
    }

    header: Pane {
        padding: control.padding
        bottomPadding: 0

        ColumnLayout {
            anchors.fill: parent

            Label {
                horizontalAlignment: Label.AlignHCenter

                text: control.title

                font.bold: true

                Layout.fillWidth: true
            }

            Divider {
                Layout.fillWidth: true
            }
        }
    }

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
                    + ((implicitHeaderHeight > 0) ? implicitHeaderHeight : 0)
                    + ((implicitFooterHeight > 0) ? implicitFooterHeight : 0)
    implicitWidth: Math.max(implicitContentWidth + leftPadding + rightPadding,
                            implicitHeaderWidth, implicitFooterWidth)
    y: (parent) ? Math.floor((parent.height - height) / 2) : 0
    x: (parent) ? Math.floor((parent.width - width) / 2) : 0

    padding: 5 + controlBackground.border.width
    bottomPadding: padding - controlBackground.border.width
    topPadding: padding - controlBackground.border.width

    closePolicy: T.Dialog.CloseOnEscape

    rightMargin: 96
    leftMargin: 96

    focus: true

    modal: true

    dim: true

    Overlay.modal: Rectangle {
        color: "#80000000"
    }
}
