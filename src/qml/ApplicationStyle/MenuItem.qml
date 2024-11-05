import QtQuick

import QtQuick.Templates as T

T.MenuItem {
    id: control

    contentItem: Text {
        color: (enabled) ? ((control.hovered
                             || control.visualFocus) ? "#fff" : "#a0f") : "#550080"

        renderType: (font.bold) ? Text.NativeRendering : Text.QtRendering

        font.bold: control.font.bold

        textFormat: Text.PlainText

        text: control.text
    }

    background: Rectangle {
        color: (enabled && (control.hovered
                            || control.visualFocus)) ? "#a0f" : "#000"
    }

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding

    padding: 5
}
