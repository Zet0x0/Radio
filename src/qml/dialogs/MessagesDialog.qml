pragma Singleton

import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import "../components"

import Radio.Player

Dialog {
    parent: DialogMaster.defaultParent
    title: "Messages"

    contentItem: ColumnLayout {
        spacing: -1

        TabBar {
            id: categoryTabBar

            Layout.fillWidth: true

            TabButton {
                text: "LibVLC"
            }

            TabButton {
                text: "App/Qt"
            }
        }

        Frame {
            Layout.fillHeight: true
            Layout.fillWidth: true

            StackLayout {
                anchors.fill: parent
                currentIndex: categoryTabBar.currentIndex

                ListView {
                    boundsBehavior: ListView.StopAtBounds
                    clip: true
                    implicitHeight: contentHeight
                    implicitWidth: contentWidth
                    spacing: 5

                    delegate: Label {
                        required property var modelData

                        contextMenuEnabled: true
                        text: modelData.display

                        Component.onCompleted: {
                            var listView = ListView.view;

                            if (implicitWidth > listView.contentWidth) {
                                listView.contentWidth = implicitWidth;
                            }
                        }
                    }
                    model: LibVlcLogMessageModel {
                    }
                }

                //                 ScrollView {
                //                    Flickable {
                //                        contentHeight: libVlcLogMessageColumn.implicitHeight
                //                        contentWidth: libVlcLogMessageColumn.implicitWidth

                //                        boundsBehavior: Flickable.StopAtBounds

                //                        clip: true

                //                        Column {
                //                            id: libVlcLogMessageColumn

                //                            spacing: 5

                //                            Repeater {
                //                                model: LibVlcLogMessageModel {}

                //                                delegate: Label {
                //                                    required property var modelData

                //                                    contextMenuEnabled: true

                //                                    text: modelData.display
                //                                }
                //                            }
                //                        }
                //                    }

                //                    ListView {
                //                        delegate: Label {
                //                            required property var modelData

                //                            contextMenuEnabled: true

                //                            text: modelData.display

                //                            Component.onCompleted: {
                //                                var listView = ListView.view

                //                                if (implicitWidth > listView.contentWidth) {
                //                                    listView.contentWidth = implicitWidth
                //                                }
                //                            }
                //                        }

                //                        boundsBehavior: ListView.StopAtBounds

                //                        model: LibVlcLogMessageModel {}

                //                        spacing: 5
                //                    }
                Label {
                    text: "app/qt"
                }
            }
        }
    }
}
