import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import QtQuick.VectorImage
import Radio.Cpp.Utilities
import Radio.ApplicationStyle

ModalDialog {
    id: control

    maximumWidth: StyleProperties.dialogs_aboutDialog_maximumWidth
    title: qsTr("About Radio")

    contentItem: RowLayout {
        VectorImage {
            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: 96
            Layout.preferredWidth: 96
            Layout.rowSpan: 2
            preferredRendererType: VectorImage.CurveRenderer
            source: "qrc:/zet0x0.github.io/icons/applicationIcon.svg"
        }

        ColumnLayout {
            Item {
                Layout.fillHeight: true
            }

            Label {
                Layout.fillWidth: true
                text: qsTr("Radio is an open-source project to browse through and play online radio stations from the internet.")
                wrapMode: Label.Wrap
            }

            Label {
                text: qsTr("Copyright (c) 2025 Zet0x0")
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }
    footer: Control {
        padding: StyleProperties.controls_padding + StyleProperties.border_width
        topPadding: StyleProperties.controls_padding

        contentItem: RowLayout {
            Item {
                Layout.fillWidth: true
            }

            Button {
                ToolTip.text: qsTr("Includes the LICENSE file and everything else about the application's internals")
                ToolTip.visible: hovered
                text: qsTr("View Repository")

                onClicked: {
                    Qt.openUrlExternally("https://github.com/Zet0x0/Radio");
                }
            }

            Button {
                ToolTip.text: qsTr("Credits to Heroicons for most of the icons in the UI (v2.2.0)")
                ToolTip.visible: hovered
                text: qsTr("Visit Heroicons")

                onClicked: {
                    Qt.openUrlExternally("https://heroicons.com");
                }
            }

            Separator {
                Layout.fillHeight: true
                horizontal: false
            }

            Button {
                ToolTip.text: qsTr("Copy version summary and close")
                ToolTip.visible: hovered
                text: qsTr("Copy and Close")

                onClicked: {
                    Utilities.copyToClipboard(Utilities.getVersionSummary());
                    control.close();
                }
            }

            Button {
                text: qsTr("Close")

                onClicked: {
                    control.close();
                }
            }
        }
    }
}
