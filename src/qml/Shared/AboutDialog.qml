import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import QtQuick.VectorImage
import Radio.Cpp.Utilities

ModalDialog {
    standardButtons: Dialog.Close
    title: qsTr("About Radio")

    contentItem: GridLayout {
        columns: 4
        rows: 4

        VectorImage {
            Layout.alignment: Qt.AlignTop
            Layout.preferredHeight: 96
            Layout.preferredWidth: 96
            Layout.rowSpan: 4
            preferredRendererType: VectorImage.CurveRenderer
            source: "qrc:/zet0x0.github.io/icons/applicationIcon.svg"
        }

        Label {
            Layout.columnSpan: 3
            Layout.fillWidth: true
            text: qsTr("Radio is an open-source project to browse through and play online radio stations from the internet.")
            wrapMode: Label.Wrap
        }

        Label {
            Layout.columnSpan: 3
            text: qsTr("Copyright (c) 2025 Zet0x0")
        }

        Separator {
            Layout.columnSpan: 3
            Layout.fillWidth: true
        }

        Button {
            ToolTip.text: qsTr("Includes the LICENSE file and everything else about the application's internals")
            ToolTip.visible: hovered
            text: qsTr("View Repository")

            onClicked: Qt.openUrlExternally("https://github.com/Zet0x0/Radio")
        }

        Separator {
            Layout.fillHeight: true
            horizontal: false
        }

        ImportantLabel {
            text: Utilities.getVersionSummary()
        }
    }
}
