import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import Radio.Clipboard

Control {
    id: stationImageRootItem

    property string imageUrl

    property string toolTip

    contentItem: StackLayout {
        currentIndex: {
            const stationImageStatus = stationImage.status

            return (stationImageStatus === AnimatedImage.Error) ? 0 : stationImageStatus
        }

        // AnimatedImage.Null, AnimatedImage.Error
        Image {
            sourceSize {
                height: height
                width: width
            }

            source: `qrc:/assets/icons/${(stationImage.status === AnimatedImage.Null) ? "applicationIcon" : "errorIcon"}.svg`

            fillMode: Image.PreserveAspectCrop
        }

        // AnimatedImage.Ready
        AnimatedImage {
            id: stationImage

            function refresh() {
                var savedSource = source.toString()

                if (!savedSource) {
                    savedSource = stationImageRootItem.imageUrl
                }

                source = ""
                source = savedSource
            }

            playing: {
                const applicationActive = Application.state === Qt.ApplicationActive

                if (!applicationActive) {
                    currentFrame = 0
                }

                return applicationActive
            }

            fillMode: AnimatedImage.PreserveAspectCrop

            source: stationImageRootItem.imageUrl
        }

        // AnimatedImage.Loading
        Label {
            text: `${Math.floor(stationImage.progress * 100)}%`

            horizontalAlignment: Label.AlignHCenter
            verticalAlignment: Label.AlignVCenter

            LoadingIndicator {
                toolTipText: "Loading..."

                anchors.fill: parent
            }
        }
    }

    background: Rectangle {
        id: stationImageBackground

        visible: stationImage.status === AnimatedImage.Ready

        border.color: "#a0f"

        color: "#000"
    }

    implicitHeight: 63 + topPadding + bottomPadding
    implicitWidth: height

    padding: stationImageBackground.border.width

    ToolTip.text: (stationImage.status === AnimatedImage.Error) ? ((!toolTip) ? "Image failed to load" : `${toolTip}\n\n(Image failed to load)`) : toolTip

    ToolTip.visible: hovered && ToolTip.text

    Menu {
        id: stationImageMenu

        onOpened: copyImageUrlAction.imageUrlSnapshot = stationImage.source

        Action {
            id: copyImageUrlAction

            property string imageUrlSnapshot: ""

            enabled: !!stationImageRootItem.imageUrl

            text: "Copy Image URL"

            onTriggered: Clipboard.setText(imageUrlSnapshot)
        }

        Action {
            enabled: !!stationImageRootItem.imageUrl

            text: "Open Image URL"

            onTriggered: Qt.openUrlExternally(
                             copyImageUrlAction.imageUrlSnapshot)
        }

        MenuSeparator {}

        Action {
            text: {
                switch (stationImage.status) {
                case AnimatedImage.Ready:
                {
                    return "Refresh"
                }
                case AnimatedImage.Loading:
                {
                    return "Stop Download"
                }
                case AnimatedImage.Error:
                {
                    return "Retry Download"
                }
                case AnimatedImage.Null:
                {
                    return "Start Download"
                }
                }
            }

            enabled: !!stationImageRootItem.imageUrl

            onTriggered: {
                if (stationImage.status === AnimatedImage.Loading) {
                    stationImage.source = ""
                } else {
                    stationImage.refresh()
                }
            }
        }
    }

    MouseArea {
        enabled: !!stationImageRootItem.imageUrl

        acceptedButtons: Qt.RightButton

        anchors.fill: parent

        onClicked: stationImageMenu.popup()
    }
}
