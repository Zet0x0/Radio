import QtQuick
import QtQuick.Controls

Dialog {
    id: control

    property bool exitOnClose: false
    required property string message

    closePolicy: Dialog.CloseOnEscape
    modal: true
    standardButtons: Dialog.Close
    x: Math.floor((parent.width - width) / 2)
    y: Math.floor((parent.height - height) / 2)

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
