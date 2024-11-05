import QtQuick

import QtQuick.Templates as T

T.TextField {
    id: control

    background: Rectangle {
        id: controlBackground

        border.color: (enabled) ? "#a0f" : "#550080"

        color: "#000"
    }

    implicitHeight: Math.max(
                        contentHeight,
                        controlPlaceholderLabel.implicitHeight) + topPadding + bottomPadding
    implicitWidth: Math.max(
                       contentWidth,
                       controlPlaceholderLabel.implicitWidth) + leftPadding + rightPadding

    verticalAlignment: T.TextField.AlignVCenter

    padding: 5 + controlBackground.border.width

    color: (enabled) ? "#a0f" : "#550080"
    placeholderTextColor: "#550080"
    selectedTextColor: "#fff"
    selectionColor: "#a0f"

    MouseArea {
        acceptedButtons: Qt.RightButton

        cursorShape: Qt.IBeamCursor

        anchors.fill: parent

        onClicked: controlContextMenu.popup()
    }

    Menu {
        id: controlContextMenu

        Action {
            enabled: control.canUndo

            text: "Undo"

            onTriggered: control.undo()
        }

        Action {
            enabled: control.canRedo

            text: "Redo"

            onTriggered: control.redo()
        }

        MenuSeparator {}

        Action {
            enabled: !!control.selectedText

            text: "Cut"

            onTriggered: control.cut()
        }

        Action {
            enabled: !!control.selectedText

            text: "Copy"

            onTriggered: control.copy()
        }

        Action {
            enabled: control.canPaste

            text: "Paste"

            onTriggered: control.paste()
        }

        Action {
            enabled: !!control.selectedText

            text: "Delete"

            onTriggered: control.remove(control.selectionStart,
                                        control.selectionEnd)
        }

        MenuSeparator {}

        Action {
            enabled: control.length !== 0

            text: "Select All"

            onTriggered: control.selectAll()
        }
    }

    Label {
        id: controlPlaceholderLabel

        height: control.height - (control.topPadding + control.bottomPadding)
        width: control.width - (control.leftPadding + control.rightPadding)
        x: control.leftPadding
        y: control.topPadding

        verticalAlignment: control.verticalAlignment

        color: control.placeholderTextColor

        visible: control.length === 0

        text: control.placeholderText

        cursorShape: Qt.IBeamCursor

        elide: Label.ElideRight
    }
}
