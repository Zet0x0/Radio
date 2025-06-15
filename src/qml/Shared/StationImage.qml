import QtQuick
import QtQuick.Controls
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
}
