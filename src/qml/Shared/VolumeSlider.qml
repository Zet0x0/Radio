import QtQuick
import QtQuick.Controls
import Radio.Cpp.Player
import Radio.ApplicationStyle

Slider {
    ToolTip.text: qsTr("Volume: %0%").arg(value)
    ToolTip.visible: hovered || visualFocus || pressed
    from: 0
    padding: StyleProperties.controls_volumeSlider_padding
    stepSize: 1
    to: 100
    value: Player.volume

    onMoved: {
        Player.setVolume(value);
        Player.setMuted(false);
    }
}
