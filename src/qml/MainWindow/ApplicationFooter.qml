import QtQuick.Controls
import QtQuick.Layouts
import Radio.Shared
import Radio.ApplicationStyle
import Radio.Cpp.Utilities
import QtQml
import QtQuick

Control {
    contentItem: ColumnLayout {
        spacing: 0

        Separator {
            Layout.fillWidth: true
        }

        ImportantLabel {
            id: footerLabel

            Layout.fillWidth: true
            font: StyleProperties.fonts_mainWindow_footerLabel
            padding: StyleProperties.controls_padding
            text: qsTr("Something should appear here...")
        }
    }

    MouseArea {
        acceptedButtons: Qt.LeftButton
        anchors.fill: parent

        onClicked: {
            DialogController.requestMessagesDialog();
        }
    }

    Connections {
        function onLogMessage(message) {
            footerLabel.text = message;
        }

        target: CppUtilities
    }
}
