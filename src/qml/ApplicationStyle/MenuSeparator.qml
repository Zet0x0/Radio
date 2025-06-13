import QtQuick
import QtQuick.Templates as T

T.MenuSeparator {
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)

    contentItem: Rectangle {
        color: StyleProperties.palette_accent
        implicitHeight: 1
    }
}
