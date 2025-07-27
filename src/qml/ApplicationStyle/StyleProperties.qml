pragma Singleton

import QtQuick

/* NOTE: It is, indeed, ugly to prefix stuff like `palette_accent`
 * instead of adding a `readonly property QtObject palette` and
 * embedding a `readonly property color accent: "#a0f"` to that,
 * but the linter, for whatever reason, does not recognize any
 * embedded properties in property `palette`, so there's that.
 */
QtObject {
    /* Border */
    readonly property int border_width: 1

    /* Controls */
    readonly property int controls_button_iconSize: 24
    readonly property int controls_iconButton_size: 32
    readonly property int controls_margins: 5
    readonly property int controls_menuBarItem_iconSize: 20
    readonly property int controls_menuItem_iconSize: 20
    readonly property int controls_menu_overlap: 1
    readonly property int controls_padding: 5
    readonly property int controls_separator_height: 1
    readonly property int controls_slider_handleHeight: 26
    readonly property int controls_slider_handleWidth: 10
    readonly property int controls_slider_implicitHeight: 4
    readonly property int controls_slider_implicitWidth: 200
    readonly property int controls_spacing: 5
    readonly property real controls_stationImage_disabledOpacity: 0.5
    readonly property int controls_stationImage_padding: 5
    readonly property int controls_stationImage_size: 96
    readonly property real controls_stationImage_stationLoadingIndicator_backgroundOpacity: 0.75
    readonly property bool controls_stationImage_stationLoadingIndicator_bounceBack: false
    readonly property var controls_stationImage_stationLoadingIndicator_frames: ["010010", "001100", "100101", "111010", "111101", "010111", "101011", "111000", "110011", "110101"]
    readonly property int controls_stationImage_stationLoadingIndicator_interval: 80
    readonly property int controls_volumeSlider_verticalPadding: 3

    /* Fonts */
    readonly property font fonts_application: ({
            family: "Segoe UI Variable",
            pointSize: 10
        })
    readonly property font fonts_dialog_titleLabel: ({
            bold: true
        })
    readonly property font fonts_elapsedLabel: ({
            family: "Consolas"
        })
    readonly property font fonts_mainWindow_footerLabel: ({
            family: "Consolas"
        })
    readonly property font fonts_nowPlayingLabel: ({
            pointSize: 12,
            bold: true
        })
    readonly property font fonts_stationImage_stationLoadingIndicator: ({
            family: "Consolas",
            pointSize: 12
        })

    /* Palette */
    readonly property color palette_accent: "#a0f"
    readonly property color palette_accent_active: "#fff"
    readonly property color palette_accent_darker: Qt.darker(palette_accent)
    readonly property color palette_accent_lighter: Qt.lighter(palette_accent)
    readonly property color palette_activeFocusBackground: "#55007f"
    readonly property color palette_background: "#000"
    readonly property color palette_dialog_modal: Qt.rgba(0.0, 0.0, 0.0, 0.5)
    readonly property color palette_dialog_modeless: Qt.rgba(0.0, 0.0, 0.0, 0.5)
    readonly property color palette_menu_modal: Qt.rgba(0.0, 0.0, 0.0, 0.5)
    readonly property color palette_menu_modeless: Qt.rgba(0.0, 0.0, 0.0, 0.5)
    readonly property color palette_stationImage_disabled: "#000"
    readonly property color palette_stationImage_stationLoadingIndicator_background: "#000"
    readonly property color palette_stationImage_stationLoadingIndicator_text: "#fff"
    readonly property color palette_text: "#a0f"
    readonly property color palette_textLink: "#d47fff"
    readonly property color palette_textLink_darker: Qt.darker(palette_textLink)
    readonly property color palette_text_active: "#fff"
    readonly property color palette_text_darker: Qt.darker(palette_text)
    readonly property color palette_text_lighter: Qt.lighter(palette_text)
}
