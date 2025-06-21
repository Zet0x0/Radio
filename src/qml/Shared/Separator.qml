import QtQuick
import Radio.ApplicationStyle

Rectangle {
    property bool horizontal: true

    color: StyleProperties.palette_accent
    implicitHeight: (horizontal) ? StyleProperties.controls_separator_height : -1
    implicitWidth: (horizontal) ? -1 : StyleProperties.controls_separator_height
}
