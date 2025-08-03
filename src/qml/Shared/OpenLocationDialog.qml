import QtQuick.Controls
import QtQuick.Layouts
import QtQuick
import Radio.Cpp.Utilities
import Radio.ApplicationStyle
import Radio.Cpp.Player

ModalDialog {
    id: control

    property alias url: urlTextField.text

    function clear() {
        urlTextField.clear();
    }

    function paste() {
        urlTextField.paste();
    }

    maximumWidth: StyleProperties.dialogs_openLocationDialog_maximumWidth
    title: qsTr("Open Location")

    contentItem: ColumnLayout {
        Label {
            text: qsTr("Enter the URL of the media you want to play:")
        }

        TextField {
            id: urlTextField

            Layout.fillWidth: true
            focus: control.visible
            placeholderText: qsTr("Enter URL here...")

            validator: UrlValidator {
            }

            onAccepted: {
                playButton.click();
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
                id: playButton

                enabled: urlTextField.acceptableInput
                text: qsTr("Play")

                onClicked: {
                    Player.playFromUrl(urlTextField.text);
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

    onOpened: {
        urlTextField.selectAll();
    }
}
