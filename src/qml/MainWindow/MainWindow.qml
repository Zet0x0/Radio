import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Radio.ApplicationStyle

ApplicationWindow {
    property alias enabled: layout.enabled

    minimumHeight: 480
    minimumWidth: 640
    title: qsTr("Radio")
    visible: true

    ColumnLayout {
        id: layout

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
}
