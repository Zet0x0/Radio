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
        contentItem: AnimatedLabel {
            bounceBack: StyleProperties.controls_stationImage_stationLoadingIndicatorBounceBack
            frameInterval: StyleProperties.controls_stationImage_stationLoadingIndicatorInterval
            frames: StyleProperties.controls_stationImage_stationLoadingIndicatorArray
            textColor: StyleProperties.palette_stationImage_stationLoadingIndicatorText
            textFont: StyleProperties.fonts_stationImage_stationLoadingIndicator
        }
    }
}
