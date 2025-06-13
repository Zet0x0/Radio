import QtQuick.Templates as T

T.Label {
    color: (enabled) ? StyleProperties.palette_text : StyleProperties.palette_darkerText
    linkColor: (enabled) ? StyleProperties.palette_textLink : StyleProperties.palette_darkerTextLink
}
