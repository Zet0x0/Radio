import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    minimumHeight: 480
    minimumWidth: 640
    title: qsTrId("application.name")
    visible: true

    ColumnLayout {
        anchors {
            fill: parent
            margins: 5
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
