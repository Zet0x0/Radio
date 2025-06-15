import QtQuick
import QtQuick.Controls
import Radio.Cpp.Player
import Radio.ApplicationStyle

// TODO: make this look disabled if muted (but allow volume change still)
// TODO: custom width property (e.g. for system menu)
Slider {
    ToolTip.text: qsTr("Volume: %0%").arg(value)
    ToolTip.visible: hovered || visualFocus || pressed
    from: 0
    padding: StyleProperties.controls_volumeSlider_padding
    palette.accent: (Player.muted) ? disabledPalette.accent : activePalette.accent
    stepSize: 1
    to: 100
    value: Player.volume

    onMoved: {
        Player.setVolume(value);
        Player.setMuted(false);
    }

    SystemPalette {
        id: activePalette

        colorGroup: SystemPalette.Active
    }

    SystemPalette {
        id: disabledPalette

        colorGroup: SystemPalette.Disabled
    }
}
