import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import "../components"

Dialog {
    id: messageDialog

    property string message

    property string details

    contentItem: ColumnLayout {
        Label {
            text: messageDialog.message

            contextMenuEnabled: true

            wrapMode: Label.Wrap

            Layout.fillWidth: true
        }

        Label {
            id: messageDialogDetailsTitleLabel

            horizontalAlignment: Label.AlignHCenter

            visible: !!messageDialog.details

            text: "Details"

            Layout.fillWidth: true
        }

        Divider {
            implicitWidth: messageDialogDetailsTitleLabel.implicitWidth

            visible: !!messageDialog.details

            Layout.alignment: Qt.AlignHCenter
        }

        Label {
            visible: !!messageDialog.details

            text: messageDialog.details

            contextMenuEnabled: true

            wrapMode: Label.Wrap

            Layout.fillWidth: true
        }
    }

    visible: true
}
