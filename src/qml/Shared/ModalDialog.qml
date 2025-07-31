import QtQuick
import QtQuick.Controls

Dialog {
    required property int maximumWidth

    closePolicy: Dialog.CloseOnEscape
    modal: true
    width: Math.min(parent.width * 0.8, maximumWidth, implicitWidth)
    x: Math.floor((parent.width - width) / 2)
    y: Math.floor((parent.height - height) / 2)
}
