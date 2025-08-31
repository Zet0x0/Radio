import QtQuick
import QtQuick.Templates as T

T.ScrollIndicator {
    id: control

    hoverEnabled: false // HACK: https://bugreports.qt.io/browse/QTBUG-114534
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, implicitContentHeight + topPadding + bottomPadding)
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, implicitContentWidth + leftPadding + rightPadding)
    padding: StyleProperties.controls_scrollIndicator_padding

    contentItem: Rectangle {
        color: StyleProperties.palette_scrollIndicator_color
        implicitHeight: StyleProperties.controls_scrollIndicator_size
        implicitWidth: StyleProperties.controls_scrollIndicator_size
        opacity: StyleProperties.controls_scrollIndicator_opacity_inactive
        visible: control.size < 1.0

        states: State {
            name: "active"
            when: control.active

            PropertyChanges {
                control.contentItem.opacity: StyleProperties.controls_scrollIndicator_opacity_active
            }
        }
        transitions: [
            Transition {
                from: "active"

                SequentialAnimation {
                    PauseAnimation {
                        duration: StyleProperties.controls_scrollIndicator_pause_duration
                    }

                    NumberAnimation {
                        duration: StyleProperties.controls_scrollIndicator_switchToInactive_duration
                        property: "opacity"
                        target: control.contentItem
                        to: StyleProperties.controls_scrollIndicator_opacity_inactive
                    }
                }
            }
        ]
    }
}
