import QtQuick.Templates as T

T.ScrollView {
    id: control

    bottomPadding: {
        const horizontalScrollBar = ScrollBar.horizontal

        return (horizontalScrollBar.visible) ? (horizontalScrollBar.height * 2) : 0
    }
    rightPadding: {
        const verticalScrollBar = ScrollBar.vertical

        return (verticalScrollBar.visible) ? (verticalScrollBar.width * 2) : 0
    }

    implicitHeight: implicitContentHeight
    implicitWidth: implicitContentWidth

    ScrollBar.horizontal: ScrollBar {
        width: control.availableWidth
        y: control.height - height
    }

    ScrollBar.vertical: ScrollBar {
        height: control.availableHeight
        x: control.width - width
    }
}
