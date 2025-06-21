import QtQuick
import QtQuick.Templates as T

T.DialogButtonBox {
    id: control

    alignment: (count === 1) ? Qt.AlignRight : undefined
    contentWidth: (contentItem as ListView)?.contentWidth
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, ((control.count === 1) ? implicitContentWidth * 2 : implicitContentWidth) + leftPadding + rightPadding)
    spacing: StyleProperties.controls_spacing

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
