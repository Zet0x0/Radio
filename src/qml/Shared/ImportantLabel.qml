/*
 * I couldn't think of a better, not-so-long, filename.
*/

import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Cpp.Utilities

Label {
    id: control

    ToolTip.text: text
    ToolTip.visible: truncated && hoverHandler.hovered
    elide: Label.ElideMiddle
    textFormat: Label.PlainText

    ContextMenu.menu: Menu {
        MenuItem {
            text: qsTr("Copy")

            onTriggered: {
                Utilities.copyToClipboard(control.text);
            }
        }
    }

    HoverHandler {
        id: hoverHandler

    }
}
