import QtQuick

import QtQuick.Controls

Loader {
    id: indicatedLoader

    property bool showLoadingIndicator: false

    asynchronous: true

    Loader {
        sourceComponent: Label {
            text: `Loading...\n${(indicatedLoader.progress * 100).toFixed(
                      1).toString().padStart(5, ' ')}%`
        }

        active: indicatedLoader.showLoadingIndicator
                && indicatedLoader.status === Loader.Loading

        asynchronous: true

        anchors.centerIn: parent
    }
}
