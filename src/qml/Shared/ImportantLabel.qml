/*
 * I couldn't think of a better, not-so-long, filename.
*/

import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle

Label {
    id: control

    property bool toolTipEnabled: true

    ToolTip.text: text
    ToolTip.visible: truncated && hoverHandler.hovered
    elide: Label.ElideRight
    textFormat: Label.PlainText

    ContextMenu.menu: CopyContextMenu {
    }

    HoverHandler {
        id: hoverHandler

        enabled: control.toolTipEnabled
    }
}
