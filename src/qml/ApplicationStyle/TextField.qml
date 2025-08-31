import QtQuick
import QtQuick.Templates as T

T.TextField {
    id: control

    color: StyleProperties.palette_text
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, contentHeight + topPadding + bottomPadding, placeholder.implicitHeight + topPadding + bottomPadding)
    implicitWidth: (implicitBackgroundWidth + leftInset + rightInset) || (Math.max(contentWidth, placeholder.implicitWidth) + leftPadding + rightPadding)
    padding: StyleProperties.controls_padding + StyleProperties.border_width
    placeholderTextColor: StyleProperties.palette_text_darker
    selectedTextColor: StyleProperties.palette_text_active
    selectionColor: StyleProperties.palette_accent
    verticalAlignment: TextInput.AlignVCenter

    T.ContextMenu.menu: Menu {
        T.Action {
            enabled: control.canUndo
            text: qsTr("Undo")

            onTriggered: control.undo()
        }

        T.Action {
            enabled: control.canRedo
            text: qsTr("Redo")

            onTriggered: control.redo()
        }

        MenuSeparator {
        }

        T.Action {
            enabled: !!control.selectedText
            text: qsTr("Cut")

            onTriggered: control.cut()
        }

        T.Action {
            enabled: !!control.selectedText
            text: qsTr("Copy")

            onTriggered: control.copy()
        }

        T.Action {
            enabled: control.canPaste
            text: qsTr("Paste")

            onTriggered: control.paste()
        }

        T.Action {
            enabled: !!control.selectedText
            text: qsTr("Delete")

            onTriggered: control.remove(control.selectionStart, control.selectionEnd)
        }

        MenuSeparator {
        }

        T.Action {
            enabled: control.length > 0
            text: qsTr("Select All")

            onTriggered: control.selectAll()
        }
    }
    background: Rectangle {
        color: StyleProperties.palette_background

        border {
            color: (control.activeFocus) ? StyleProperties.palette_accent_lighter : StyleProperties.palette_accent
            width: StyleProperties.border_width
        }
    }

    Text {
        id: placeholder

        color: control.placeholderTextColor
        elide: Text.ElideRight
        font: control.font
        height: control.height - (control.topPadding + control.bottomPadding)
        renderType: control.renderType
        text: control.placeholderText
        verticalAlignment: control.verticalAlignment
        visible: !control.length && !control.preeditText && (!control.activeFocus || control.horizontalAlignment !== Qt.AlignHCenter)
        width: control.width - (control.leftPadding + control.rightPadding)
        x: control.leftPadding
        y: control.topPadding
    }
}
