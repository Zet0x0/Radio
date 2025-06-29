import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts
import Radio.Shared

T.MenuBar {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)

    contentItem: ColumnLayout {
        spacing: 0

        Control {
            Layout.fillWidth: true
            leftPadding: StyleProperties.controls_padding
            rightPadding: StyleProperties.controls_padding

            contentItem: Row {
                spacing: StyleProperties.controls_spacing

                Repeater {
                    model: control.contentModel
                }
            }
        }

        Separator {
            Layout.fillWidth: true
        }
    }
    delegate: MenuBarItem {
    }
}
