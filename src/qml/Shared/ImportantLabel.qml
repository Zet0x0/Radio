/*
 * I couldn't think of a better, not-so-long, filename.
*/

import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Utilities

Label {
    id: control

    property bool toolTipEnabled: true

    ToolTip.text: text
    ToolTip.visible: truncated && hoverHandler.hovered
    elide: Label.ElideMiddle
    textFormat: Label.PlainText

    ContextMenu.menu: CopyContextMenu {
    }

    HoverHandler {
        id: hoverHandler

        enabled: control.toolTipEnabled
    }
}
