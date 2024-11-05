import QtQuick

import QtQuick.Templates as T

import Radio.Clipboard

T.Label {
    id: control

    property int cursorShape: Qt.ArrowCursor

    property bool contextMenuEnabled: false

    property double fontSizeMultiplier: 1.

    renderType: (font.bold) ? T.Label.NativeRendering : T.Label.QtRendering

    color: (enabled) ? "#a0f" : "#550080"

    textFormat: T.Label.PlainText

    ToolTip.visible: controlHoverHandler.hovered && truncated

    ToolTip.text: text

    Component.onCompleted: font.pixelSize *= fontSizeMultiplier

    HoverHandler {
        id: controlHoverHandler
    }

    Loader {
        sourceComponent: MouseArea {
            enabled: control.contextMenuEnabled

            cursorShape: control.cursorShape

            acceptedButtons: Qt.RightButton

            onClicked: controlMenuLoader.item.popup()
        }

        active: control.cursorShape !== Qt.ArrowCursor
                || control.contextMenuEnabled

        anchors.fill: parent
    }

    Loader {
        id: controlMenuLoader

        sourceComponent: Menu {
            onOpened: controlMenuCopyAction.textSnapshot = control.text

            Action {
                id: controlMenuCopyAction

                property string textSnapshot: ""

                text: "Copy"

                onTriggered: Clipboard.setText(textSnapshot)
            }
        }

        active: control.contextMenuEnabled
    }
}
