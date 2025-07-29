import QtQuick
import Radio.ApplicationStyle

Rectangle {
    property bool horizontal: true

    color: (enabled) ? StyleProperties.palette_accent : StyleProperties.palette_accent_darker
    implicitHeight: (horizontal) ? StyleProperties.controls_separator_height : 0
    implicitWidth: (horizontal) ? 0 : StyleProperties.controls_separator_height
}
