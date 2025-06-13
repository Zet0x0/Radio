import QtQuick
import QtQuick.Templates as T

T.Menu {
    id: control

    contentWidth: {
        var result = 0;

        for (var i = 0; i < count; ++i) {
            result = Math.max(itemAt(i).implicitWidth, result);
        }

        return result;
    }
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    margins: 0 // NOTE: values above 0 make the menu have a stroke and shrink to 0 pixels
    overlap: StyleProperties.controls_menu_overlap
    padding: StyleProperties.controls_padding + StyleProperties.border_width

    T.Overlay.modal: Rectangle {
        color: StyleProperties.palette_menu_modalShadow
    }
    T.Overlay.modeless: Rectangle {
        color: StyleProperties.palette_menu_modelessShadow
    }
    background: Rectangle {
        color: StyleProperties.palette_background
        implicitWidth: control.contentWidth

        border {
            color: StyleProperties.palette_accent
            width: StyleProperties.border_width
        }
    }
    contentItem: ListView {
        clip: true
        currentIndex: control.currentIndex
        implicitHeight: contentHeight
        interactive: (Window.window) ? (contentHeight + control.topPadding + control.bottomPadding) > control.height : false
        model: control.contentModel
        spacing: StyleProperties.controls_spacing
    }
    delegate: MenuItem {
    }
}
