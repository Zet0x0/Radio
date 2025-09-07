import QtQuick.Controls
import Radio.Cpp

Menu {
    id: control

    Action {
        text: qsTr("Copy")

        onTriggered: {
            CppUtilities.copyToClipboard((control.parent as Label).text);
        }
    }
}
