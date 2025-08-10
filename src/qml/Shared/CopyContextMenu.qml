import QtQuick.Controls
import Radio.Cpp.Utilities

Menu {
    id: control

    Action {
        text: qsTr("Copy")

        onTriggered: {
            CppUtilities.copyToClipboard((control.parent as Label).text);
        }
    }
}
