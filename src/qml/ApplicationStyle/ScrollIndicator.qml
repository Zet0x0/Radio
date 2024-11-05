import QtQuick

import QtQuick.Templates as T

T.ScrollIndicator {
    id: control

    contentItem: Rectangle {
        transitions: Transition {
            from: "active"

            SequentialAnimation {
                PauseAnimation {
                    duration: 500
                }

                NumberAnimation {
                    target: control.contentItem

                    property: "opacity"

                    duration: 0

                    to: 0.
                }
            }
        }

        states: State {
            when: control.active

            name: "active"

            PropertyChanges {
                control.contentItem.opacity: .5
            }
        }

        opacity: (control.active) ? .5 : 0.

        visible: control.size < 1.

        implicitHeight: 1
        implicitWidth: 1

        color: "#a0f"
    }

    implicitHeight: implicitContentHeight
    implicitWidth: implicitContentWidth
}
