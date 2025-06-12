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
    readonly property int controls_margins: 5
    readonly property int controls_padding: 5
    readonly property int controls_spacing: 5

    /* Palette */
    readonly property color palette_accent: "#a0f"
    readonly property color palette_background: "#000"
    readonly property color palette_text: "#a0f"
}
