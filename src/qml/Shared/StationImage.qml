import QtQuick
import Radio.Cpp.Player
import Radio.ApplicationStyle
import QtQuick.VectorImage

Control {
    implicitHeight: StyleProperties.controls_stationImage_size
    implicitWidth: StyleProperties.controls_stationImage_size
    padding: StyleProperties.controls_stationImage_padding + StyleProperties.border_width

    background: Rectangle {
        color: StyleProperties.palette_background

        border {
            color: (enabled) ? StyleProperties.palette_accent : StyleProperties.palette_accent_darker
            width: StyleProperties.border_width
        }
    }
    contentItem: Image {
        id: control

        cache: false
        fillMode: Image.PreserveAspectCrop
        source: Player.station.imageUrl

        sourceSize {
            height: height
            width: width
        }

        VectorImage {
            anchors.fill: parent
            fillMode: Image.PreserveAspectCrop
            preferredRendererType: VectorImage.CurveRenderer
            source: "qrc:/zet0x0.github.io/icons/applicationIcon.svg"
            visible: control.status !== Image.Ready
        }

        Control {
            anchors.fill: parent
            visible: Player.state === Player.LOADING

            background: Rectangle {
                color: StyleProperties.palette_stationImage_stationLoadingIndicator_background
                opacity: StyleProperties.controls_stationImage_stationLoadingIndicator_backgroundOpacity
            }
            contentItem: AnimatedLabel {
                bounceBack: StyleProperties.controls_stationImage_stationLoadingIndicator_bounceBack
                frameInterval: StyleProperties.controls_stationImage_stationLoadingIndicator_interval
                frames: StyleProperties.controls_stationImage_stationLoadingIndicator_frames
                textColor: StyleProperties.palette_stationImage_stationLoadingIndicator_text
                textFont: StyleProperties.fonts_stationImage_stationLoadingIndicator
            }
        }

        Rectangle {
            anchors.fill: parent
            color: StyleProperties.palette_stationImage_disabled
            opacity: StyleProperties.controls_stationImage_disabledOpacity
            visible: !control.enabled
        }
    }
}
