import QtQuick.Layouts
import Radio.Cpp.Player
import Radio.ApplicationStyle

ColumnLayout {
    id: layout

    enabled: Player.initialized

    anchors {
        fill: parent
        margins: StyleProperties.controls_margins
    }

    TopLayout {
        Layout.fillWidth: true
    }

    BottomLayout {
        Layout.fillHeight: true
        Layout.fillWidth: true
    }
}
