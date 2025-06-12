pragma Singleton

import QtQuick

/* NOTE: It is, indeed, ugly to prefix stuff like `palette_accent`
 * instead of adding a `readonly property QtObject palette` and
 * embedding a `readonly property color accent: "#a0f"` to that,
 * but the linter, for whatever reason, does not recognize any
 * embedded properties in property `palette`, so there's that.
 */
QtObject {
    readonly property color palette_accent: "#a0f"
    readonly property color palette_background: "#000"
}
