import QtQuick
import QtQuick.Templates as T
import QtQuick.Layouts
import Radio.Shared

T.MenuBar {
    id: control

    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding + StyleProperties.controls_separator_height) // HACK: without the +separator_height, the height is quite inaccurate
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)

    contentItem: ColumnLayout {
        spacing: 0

        Control {
            Layout.fillWidth: true
            horizontalPadding: StyleProperties.controls_padding

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
