import QtQuick

import QtQuick.Templates as T

import "../components"

T.Menu {
    id: control

    contentItem: GenericListView {
        interactive: {
            const window = Window.window

            return (window) ? ((implicitHeight + control.topPadding
                                + control.bottomPadding) > window.height) : false
        }

        model: control.contentModel
    }

    background: Rectangle {
        id: controlBackground

        border.color: "#a0f"

        color: "#000"
    }

    delegate: MenuItem {}

    implicitWidth: {
        var biggestItemWidth = 0

        for (var i = 0; i < count; ++i) {
            const itemImplicitWidth = itemAt(i).implicitWidth

            if (biggestItemWidth < itemImplicitWidth) {
                biggestItemWidth = itemImplicitWidth
            }
        }

        return biggestItemWidth + leftPadding + rightPadding
    }
    implicitHeight: implicitContentHeight + topPadding + bottomPadding

    padding: 5 + controlBackground.border.width

    focus: true

    margins: 5
}
