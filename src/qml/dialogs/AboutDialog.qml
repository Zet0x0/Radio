pragma Singleton

import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import Radio.CppUtilities

Dialog {
    id: aboutDialog

    buttonAlignment: Qt.AlignRight
    parent: DialogMaster.defaultParent
    popupType: Popup.Native
    title: "About Radio"

    buttons: RowLayout {
        Button {
            ToolTip.text: "This application uses some of the modified icons from this project."
            ToolTip.visible: hovered
            text: "Visit heroicons.com"

            onClicked: Qt.openUrlExternally("https://heroicons.com")
        }

        Button {
            ToolTip.text: "Includes the LICENSE file and the source code of the application."
            ToolTip.visible: hovered
            text: "View Repository"

            onClicked: Qt.openUrlExternally("https://github.com/Zet0x0/Radio")
        }

        Button {
            text: "Close"

            onClicked: aboutDialog.close()
        }
    }
    contentItem: GridLayout {
        columns: 2
        rows: 3

        Image {
            Layout.alignment: Qt.AlignTop
            Layout.rowSpan: 3
            source: "qrc:/assets/icons/applicationIcon.svg"
        }

        Label {
            Layout.fillWidth: true
            text: "Radio is an open-source project to browse through and play online radio stations from multiple sources."
            wrapMode: Label.Wrap
        }

        Label {
            text: `(C) ${(new Date).getFullYear()} Zet`
        }

        Label {
            color: "#550080"
            contextMenuEnabled: true
            text: `App: ${Application.version} | LibVLC: ${CppUtilities.libVlcVersion()} | Qt: ${CppUtilities.qtVersion()}`
        }
    }
}
