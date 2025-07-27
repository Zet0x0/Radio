import QtQuick
import QtQuick.Controls

Dialog {
    closePolicy: Dialog.CloseOnEscape
    modal: true
    x: Math.floor((parent.width - width) / 2)
    y: Math.floor((parent.height - height) / 2)
}
