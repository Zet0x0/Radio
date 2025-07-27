import QtQuick
import QtQuick.Controls

ModalDialog {
    id: control

    property bool exitOnClose: false
    required property string message

    standardButtons: Dialog.Close

    contentItem: ImportantLabel {
        text: control.message
        toolTipEnabled: false
    }

    onClosed: {
        if (exitOnClose) {
            Qt.exit(2);
        }
    }
}
