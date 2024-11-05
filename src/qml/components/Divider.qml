import QtQuick

Rectangle {
    property int orientation: Qt.Horizontal

    implicitHeight: (orientation === Qt.Horizontal) ? 1 : 10
    implicitWidth: (orientation === Qt.Horizontal) ? 10 : 1

    color: "#a0f"
}
