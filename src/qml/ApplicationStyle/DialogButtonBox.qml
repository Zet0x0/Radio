import QtQuick
import QtQuick.Templates as T

T.DialogButtonBox {
    id: control

    alignment: Qt.AlignRight
    contentWidth: (contentItem as ListView)?.contentWidth
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    padding: StyleProperties.controls_padding + StyleProperties.border_width
    spacing: StyleProperties.controls_spacing
    topPadding: StyleProperties.controls_padding

    contentItem: ListView {
        boundsBehavior: Flickable.StopAtBounds
        implicitWidth: contentWidth
        model: control.contentModel
        orientation: ListView.Horizontal
        snapMode: ListView.SnapToItem
        spacing: control.spacing
    }
    delegate: Button {
    }
}
