import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import QtQuick.VectorImage
import Radio.Cpp
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
            preferredRendererType: VectorImage.CurveRenderer
            source: "qrc:/zet0x0.github.io/icons/application-icon.svg"
        }

        ColumnLayout {
            Label {
                Layout.fillWidth: true
                text: qsTr("Radio is an open-source project to browse through and play online radio stations from the internet.")
                wrapMode: Label.Wrap
            }

            Label {
                text: qsTr("Copyright (c) 2025 Zet0x0")
            }

            Separator {
                Layout.fillWidth: true
            }

            Label {
                text: qsTr(`The App: Radio v. %0 - <a href="https://github.com/Zet0x0/Radio">View Repository</a><br>
                           UI: Qt v. %1 - <a href="https://qt.io">Visit qt.io</a><br>
                           Player: libmpv v. %2 - <a href="https://mpv.io">Visit mpv.io</a><br>
                           Icons: Tabler Icons v. 3.34.1 - <a href="https://tabler.io/icons">Visit Tabler Icons</a>`).arg(Qt.application.version).arg(CppUtilities.getQtVersion()).arg(CppUtilities.getLibMpvVersion())
                textFormat: Label.RichText

                onLinkActivated: link => {
                    Qt.openUrlExternally(link);
                }

                HoverHandler {
                    cursorShape: Qt.PointingHandCursor
                    enabled: !!parent.hoveredLink
                }
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
                ToolTip.text: qsTr("Copy version summary and close")
                ToolTip.visible: hovered
                text: qsTr("Copy and Close")

                onClicked: {
                    CppUtilities.copyToClipboard(CppUtilities.getVersionSummary());
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
