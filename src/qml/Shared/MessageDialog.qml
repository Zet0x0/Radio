import QtQuick
import QtQuick.Controls

ModalDialog {
    id: control

    required property string message
    property bool quitOnClose: false

    standardButtons: Dialog.Close

    contentItem: ImportantLabel {
        text: control.message
        toolTipEnabled: false
    }

    onClosed: {
        if (quitOnClose) {
            Qt.exit(2);
        }
    }
}
