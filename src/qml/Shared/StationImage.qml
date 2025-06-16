import QtQuick
import Radio.Cpp.Player
import Radio.ApplicationStyle

Image {
    id: stationImage

    cache: false
    fillMode: Image.PreserveAspectCrop
    height: StyleProperties.controls_stationImage_size
    source: Player.station.imageUrl
    width: StyleProperties.controls_stationImage_size

    sourceSize {
        height: height
        width: width
    }

    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "qrc:/zet0x0.github.io/icons/applicationIcon.svg"
        visible: stationImage.status !== Image.Ready

        sourceSize {
            height: height
            width: width
        }
    }

    Control {
        anchors.fill: parent
        visible: Player.state === Player.LOADING

        background: Rectangle {
            color: StyleProperties.palette_stationImage_stationLoadingIndicatorBackground
            opacity: StyleProperties.controls_stationImage_stationLoadingIndicatorBackgroundOpacity
        }
        contentItem: Label {
            id: stationLoadingIndicatorLabel

            property int currentArrayIndex: 0

            color: StyleProperties.palette_stationImage_stationLoadingIndicatorText
            font: StyleProperties.fonts_stationImage_stationLoadingIndicator
            horizontalAlignment: Qt.AlignHCenter
            text: StyleProperties.controls_stationImage_stationLoadingIndicatorArray[currentArrayIndex]
            verticalAlignment: Qt.AlignVCenter

            Timer {
                property bool reverse: false

                interval: StyleProperties.controls_stationImage_stationLoadingIndicatorInterval
                repeat: true
                running: stationLoadingIndicatorLabel.visible

                onTriggered: {
                    if (reverse) {
                        --stationLoadingIndicatorLabel.currentArrayIndex;

                        if (stationLoadingIndicatorLabel.currentArrayIndex === 0) {
                            reverse = false;
                        }

                        return;
                    }

                    if (stationLoadingIndicatorLabel.currentArrayIndex === StyleProperties.controls_stationImage_stationLoadingIndicatorArray.length - 1) {
                        if (StyleProperties.controls_stationImage_stationLoadingIndicatorBounceBack) {
                            reverse = true;
                            --stationLoadingIndicatorLabel.currentArrayIndex;

                            return;
                        }

                        stationLoadingIndicatorLabel.currentArrayIndex = 0;

                        return;
                    }

                    ++stationLoadingIndicatorLabel.currentArrayIndex;
                }
            }
        }
    }
}
