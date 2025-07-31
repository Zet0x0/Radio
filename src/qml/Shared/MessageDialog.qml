import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle

ModalDialog {
    id: control

    required property string message
    property bool quitOnClose: false

    maximumWidth: StyleProperties.dialogs_messageDialog_maximumWidth
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
