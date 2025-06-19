import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle

Label {
    id: control

    /* frames */
    property int _currentFrame: 0 // private
    property bool bounceBack: false
    property alias frameInterval: timer.interval
    required property var frames
    /* text */
    property alias textColor: control.color
    property alias textFont: control.font

    horizontalAlignment: Qt.AlignHCenter
    text: frames[_currentFrame]
    verticalAlignment: Qt.AlignVCenter

    Timer {
        id: timer

        property bool _reverse: false

        repeat: true
        running: control.visible

        onTriggered: {
            if (_reverse) {
                --control._currentFrame;

                if (control._currentFrame === 0) {
                    _reverse = false;
                }

                return;
            }

            if (control._currentFrame === control.frames.length - 1) {
                if (control.bounceBack) {
                    _reverse = true;
                    --control._currentFrame;

                    return;
                }

                control._currentFrame = 0;

                return;
            }

            ++control._currentFrame;
        }
    }
}
