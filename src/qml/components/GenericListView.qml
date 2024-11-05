import QtQuick

import QtQuick.Controls

ListView {
    boundsBehavior: ListView.StopAtBounds

    implicitHeight: contentHeight

    clip: true

    // ScrollIndicator.horizontal: ScrollIndicator {}
    // ScrollIndicator.vertical: ScrollIndicator {}
    ScrollBar.horizontal: ScrollBar {}
    ScrollBar.vertical: ScrollBar {}
}
