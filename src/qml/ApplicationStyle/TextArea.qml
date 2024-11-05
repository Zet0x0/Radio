import QtQuick

import QtQuick.Templates as T

T.TextArea {
    implicitHeight: contentHeight + topPadding + bottomPadding
    implicitWidth: contentWidth + leftPadding + rightPadding

    selectedTextColor: "#fff"
    selectionColor: "#a0f"
    color: "#a0f"

    textFormat: Qt.RichText
}
