import QtQuick
import QtQuick.Controls
import Radio.Cpp.Player
import Radio.ApplicationStyle

Slider {
    ToolTip.text: qsTr("Volume: %0%").arg(value)
    ToolTip.visible: hovered || visualFocus || pressed
    from: 0
    padding: 0
    stepSize: 1
    to: 100
    value: Player.volume
    verticalPadding: StyleProperties.controls_volumeSlider_verticalPadding

    onMoved: {
        Player.setVolume(value);
    }
}
