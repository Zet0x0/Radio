import QtQuick
import QtQuick.Controls

Dialog {
    required property int maximumWidth

    closePolicy: Dialog.CloseOnEscape
    modal: true
    width: Math.max(Math.min(parent.width, maximumWidth, implicitWidth), implicitHeaderWidth, implicitFooterWidth)
    x: Math.floor((parent.width - width) / 2)
    y: Math.floor((parent.height - height) / 2)
}
