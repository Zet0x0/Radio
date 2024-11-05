pragma Singleton

import QtQuick.Controls
import QtQuick.Layouts

import Radio.CppUtilities
import Radio.Validators
import Radio.Player

Dialog {
    id: openLocationDialog

    function selectAll() {
        openLocationDialogUrlTextField.selectAll()
    }

    function paste() {
        if (openLocationDialogUrlTextField.canPaste) {
            openLocationDialogUrlTextField.paste()
        }
    }

    contentItem: ColumnLayout {
        Label {
            text: "Enter the URL of the media you want to play:"

            wrapMode: Label.Wrap

            Layout.fillWidth: true
        }

        TextField {
            id: openLocationDialogUrlTextField

            validator: UrlValidator {}

            placeholderText: "Enter URL here..."

            focus: openLocationDialog.visible

            Layout.fillWidth: true
        }
    }

    buttons: RowLayout {
        RowLayout {
            enabled: !!openLocationDialogUrlTextField.length

            Button {
                text: "Play"

                onClicked: {
                    Player.setStation(CppUtilities.stationFromJson({
                                                                       "streamUrls": [openLocationDialogUrlTextField.text]
                                                                   }))

                    Player.play()

                    openLocationDialog.close()
                }
            }

            Button {
                text: "Apply"

                onClicked: {
                    Player.setStation(CppUtilities.stationFromJson({
                                                                       "streamUrls": [openLocationDialogUrlTextField.text]
                                                                   }))

                    openLocationDialog.close()
                }
            }
        }

        Button {
            text: "Cancel"

            onClicked: openLocationDialog.close()
        }
    }

    parent: DialogMaster.defaultParent

    buttonAlignment: Qt.AlignRight

    title: "Open Location"

    onClosed: openLocationDialogUrlTextField.clear()
}
