import QtQuick

import QtQuick.Templates as T

T.TabBar {
    id: control

    property alias listViewSection: controlContentItem.section

    property bool vertical: false

    contentItem: ListView {
        id: controlContentItem

        orientation: (control.vertical) ? ListView.Vertical : ListView.Horizontal

        boundsBehavior: ListView.StopAtBounds

        currentIndex: control.currentIndex

        model: control.contentModel

        spacing: control.spacing

        interactive: false

        Keys.onPressed: event => {
                            switch (event.key) {
                                case Qt.Key_Right:
                                case Qt.Key_Down:
                                {
                                    event.accepted = true

                                    incrementCurrentIndex()

                                    break
                                }
                                case Qt.Key_Left:
                                case Qt.Key_Up:
                                {
                                    event.accepted = true

                                    decrementCurrentIndex()

                                    break
                                }
                                default:
                                {
                                    event.accepted = false

                                    break
                                }
                            }
                        }

        MouseArea {
            anchors.fill: parent

            onClicked: mouse => {
                           mouse.accepted = true

                           const clickedIndex = controlContentItem.indexAt(
                               mouse.x, mouse.y)

                           if (clickedIndex !== -1) {
                               controlContentItem.currentIndex = clickedIndex
                           }
                       }

            onWheel: wheel => {
                         wheel.accepted = true

                         const angleDelta = wheel.angleDelta

                         if (angleDelta.x < 0 || angleDelta.y < 0) {
                             controlContentItem.incrementCurrentIndex()
                         } else {
                             controlContentItem.decrementCurrentIndex()
                         }
                     }
        }
    }

    implicitHeight: contentHeight
    implicitWidth: contentWidth

    spacing: 5

    Component.onCompleted: {
        const contentModelCount = contentModel.count

        var biggestTabWidth = 0

        for (var i = 0; i < contentModelCount; ++i) {
            const itemImplicitWidth = contentModel.get(i).implicitWidth

            if (itemImplicitWidth > biggestTabWidth) {
                biggestTabWidth = itemImplicitWidth
            }
        }

        for (var i = 0; i < contentModelCount; ++i) {
            contentModel.get(i).width = biggestTabWidth
        }

        if (vertical) {
            contentWidth = biggestTabWidth
        }
    }
}
