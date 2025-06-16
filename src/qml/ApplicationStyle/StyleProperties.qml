pragma Singleton

import QtQuick

/* NOTE: It is, indeed, ugly to prefix stuff like `palette_accent`
 * instead of adding a `readonly property QtObject palette` and
 * embedding a `readonly property color accent: "#a0f"` to that,
 * but the linter, for whatever reason, does not recognize any
 * embedded properties in property `palette`, so there's that.
 */
// TODO: maybe just make this a Cpp thing
QtObject {
    /* Border */
    readonly property int border_width: 1

    /* Controls */
    readonly property int controls_button_iconSize: 24
    readonly property int controls_iconButton_size: 32
    readonly property int controls_margins: 5
    readonly property int controls_menuItem_iconSize: 20
    readonly property int controls_menu_overlap: 1
    readonly property int controls_padding: 5
    readonly property int controls_slider_horizontalSwapHandleHeight: 26
    readonly property int controls_slider_horizontalSwapHandleWidth: 10
    readonly property int controls_slider_horizontalSwapImplicitHeight: 4
    readonly property int controls_slider_horizontalSwapImplicitWidth: 200
    readonly property int controls_spacing: 5
    readonly property int controls_stationImage_size: 96
    readonly property var controls_stationImage_stationLoadingIndicatorArray: ["010010", "001100", "100101", "111010", "111101", "010111", "101011", "111000", "110011", "110101"]
    readonly property real controls_stationImage_stationLoadingIndicatorBackgroundOpacity: 0.75
    readonly property bool controls_stationImage_stationLoadingIndicatorBounceBack: false
    readonly property int controls_stationImage_stationLoadingIndicatorInterval: 80
    readonly property int controls_volumeSlider_padding: 3

    /* Fonts */
    readonly property font fonts_application: ({
            family: "Segoe UI Variable",
            pointSize: 10
        })
    readonly property font fonts_mainWindow_elapsedLabel: ({
            family: "Consolas"
        })
    readonly property font fonts_mainWindow_nowPlayingLabel: ({
            pointSize: 12,
            bold: true
        })
    readonly property font fonts_stationImage_stationLoadingIndicator: ({
            family: "Consolas",
            pointSize: 12
        })

    /* Palette */
    readonly property color palette_accent: "#a0f"
    readonly property color palette_activeAccent: "#fff"
    readonly property color palette_activeFocusBackground: "#55007f"
    readonly property color palette_activeText: "#fff"
    readonly property color palette_background: "#000"
    readonly property color palette_darkerAccent: Qt.darker(palette_accent)
    readonly property color palette_darkerText: Qt.darker(palette_text)
    readonly property color palette_darkerTextLink: Qt.darker(palette_textLink)
    readonly property color palette_lighterAccent: Qt.lighter(palette_accent)
    readonly property color palette_lighterText: Qt.lighter(palette_text)
    readonly property color palette_menu_modalShadow: "#00000080"
    readonly property color palette_menu_modelessShadow: "#0000001f"
    readonly property color palette_stationImage_stationLoadingIndicatorBackground: "#000"
    readonly property color palette_stationImage_stationLoadingIndicatorText: "#fff"
    readonly property color palette_text: "#a0f"
    readonly property color palette_textLink: "#d47fff"
}
