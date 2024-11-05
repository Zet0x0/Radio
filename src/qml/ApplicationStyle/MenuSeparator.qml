import QtQuick.Templates as T

import "../components"

T.MenuSeparator {
    contentItem: Divider {}

    implicitHeight: implicitContentHeight + topPadding + bottomPadding
    implicitWidth: implicitContentWidth + leftPadding + rightPadding

    bottomPadding: 5
    topPadding: 5
}
