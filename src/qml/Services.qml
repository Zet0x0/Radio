import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "./components"

// commented out services == not implemented
RowLayout {
    spacing: -1

    ListModel {
        id: serviceModel

        ListElement {
            divider: false
            friendlyName: "Radio Garden"
        }

        ListElement {
            divider: false
            friendlyName: "radio.net"
        }

        ListElement {
            divider: false
            friendlyName: "Zeno.FM"
        }

        // ListElement {
        //     divider: false
        //     friendlyName: "Radio-Tochka.com"
        // }

        // ListElement {
        //     divider: false
        //     friendlyName: "Xiph Directory"
        // }

        // ListElement {
        //     divider: false
        //     friendlyName: "RadioBrowser"
        // }

        // ListElement {
        //     divider: false
        //     friendlyName: "RadioPlayer"
        // }

        // ListElement {
        //     divider: false
        //     friendlyName: "101.ru"
        // }

        ListElement {
            divider: true
            friendlyName: ""
        }

        // ListElement {
        //     divider: false
        //     friendlyName: "Added Stations"
        // }

        ListElement {
            divider: false
            friendlyName: "Favorites"
        }
    }

    ListView {
        id: serviceList

        property int serviceLoadedCount: 0

        function adjustWidth() {
            for (var i = 0; i < count; ++i) {
                const itemImplicitWidth = itemAtIndex(i).children[0].implicitWidth;

                if (itemImplicitWidth > implicitWidth) {
                    implicitWidth = itemImplicitWidth;
                }
            }
        }

        // this function is never expecting a divider to be in start or end
        function updateIndex(newIndex, action) {
            if (newIndex === currentIndex) {
                return;
            }

            var itemAtNewIndex = itemAtIndex(newIndex);

            if (action !== "=" && itemAtNewIndex.divider) {
                updateIndex(action === "+" ? newIndex + 1 : newIndex - 1, action);

                return;
            }

            itemAtIndex(currentIndex).children[0].checked = false;
            itemAtNewIndex.children[0].checked = true;

            currentIndex = newIndex;
        }

        Layout.fillHeight: true
        boundsBehavior: ListView.StopAtBounds
        clip: true
        model: serviceModel
        spacing: 5

        delegate: Column {
            required property bool divider
            required property string friendlyName
            required property int index

            spacing: 5

            Component.onCompleted: ++serviceList.serviceLoadedCount

            Button {
                checked: serviceList.currentIndex === index
                text: friendlyName
                visible: !divider
                width: serviceList.width

                onClicked: serviceList.updateIndex(index, "=")
            }

            Divider {
                visible: divider
                width: serviceList.width
            }
        }

        Keys.onPressed: event => {
            switch (event.key) {
            case Qt.Key_Left:
            case Qt.Key_Up:
                if (currentIndex > 0) {
                    updateIndex(currentIndex - 1, "-");
                }

                break;
            case Qt.Key_Right:
            case Qt.Key_Down:
                if (currentIndex !== count - 1) {
                    updateIndex(currentIndex + 1, "+");
                }

                break;
            default:
                event.accepted = false;

                return;
            }

            event.accepted = true;
        }
        onServiceLoadedCountChanged: {
            if (serviceLoadedCount === count) {
                Qt.callLater(adjustWidth);
            }
        }

        MouseArea {
            acceptedButtons: Qt.NoButton
            anchors.fill: parent

            onWheel: wheel => {
                const angleDelta = wheel.angleDelta;
                const currentIndex = serviceList.currentIndex;

                if (angleDelta.x < 0 || angleDelta.y < 0) {
                    if (currentIndex + 1 < serviceList.count) {
                        serviceList.updateIndex(currentIndex + 1, "+");
                    }
                } else {
                    if (currentIndex - 1 > -1) {
                        serviceList.updateIndex(currentIndex - 1, "-");
                    }
                }
            }
        }
    }

    Frame {
        Layout.fillHeight: true
        Layout.fillWidth: true

        // initial value for currentIndex never works if i use Repeater with model set to serviceModel, :(
        StackLayout {
            anchors.fill: parent
            currentIndex: serviceList.currentIndex

            onCurrentIndexChanged: itemAt(currentIndex).active = true

            OptionallyIndicatedLoader {
                active: false
                showLoadingIndicator: true
                source: "qrc:/qml/servicePages/RadioGarden.qml"
            }

            OptionallyIndicatedLoader {
                active: false
                showLoadingIndicator: true
                source: "qrc:/qml/servicePages/RadioNet.qml"
            }

            OptionallyIndicatedLoader {
                active: false
                showLoadingIndicator: true
                source: "qrc:/qml/servicePages/ZenoFM.qml"
            }

            // OptionallyIndicatedLoader {
            //     active: false
            //     showLoadingIndicator: true
            //     source: "qrc:/qml/servicePages/RadioTochka.qml"
            // }

            // OptionallyIndicatedLoader {
            //     active: false
            //     showLoadingIndicator: true
            //     source: "qrc:/qml/servicePages/XiphDirectory.qml"
            // }

            // OptionallyIndicatedLoader {
            //     active: false
            //     showLoadingIndicator: true
            //     source: "qrc:/qml/servicePages/RadioBrowser.qml"
            // }

            // OptionallyIndicatedLoader {
            //     active: false
            //     showLoadingIndicator: true
            //     source: "qrc:/qml/servicePages/RadioPlayer.qml"
            // }

            // OptionallyIndicatedLoader {
            //     active: false
            //     showLoadingIndicator: true
            //     source: "qrc:/qml/servicePages/OneOhOneRu.qml"
            // }

            Label {
                text: "You're not supposed to see this text."
            }

            // OptionallyIndicatedLoader {
            //     active: false
            //     showLoadingIndicator: true
            //     source: "qrc:/qml/servicePages/AddedStations.qml"
            // }

            OptionallyIndicatedLoader {
                active: false
                showLoadingIndicator: true
                source: "qrc:/qml/servicePages/Favorites.qml"
            }
        }
    }
}
