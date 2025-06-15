/* https://github.com/Zet0x0/SampleCustomSystemTray */

import QtQuick
import QtQuick.Controls
import Radio.ApplicationStyle
import Radio.Shared
import QtQuick.Layouts
import Radio.MainWindow

Window {
    id: window

    required property MainWindow applicationWindow

    function popup(position) {
        /*
         * make it so the menu would never overflow out of screen by
         * moving the xy origin point from the top-left corner to
         * the bottom-left corner
         */
        x = Math.max(0, Math.min(Screen.width - width, position.x));
        y = Math.max(0, Math.min(Screen.height - height, position.y - height + 1)); /* `+ 1` for perfect alignment */

        show();
        menu.popup();
    }

    color: "#00000000" /* make the window transparent to support menus with rounded edges */
    flags: Qt.Popup | Qt.NoDropShadowWindowHint
    height: menu.height
    width: menu.width

    Menu {
        id: menu

        font: StyleProperties.fonts_application // has to be explicitly specified here

        onClosed: {
            window.hide();
        }

        Control {
            contentItem: ColumnLayout {
                StationImage {
                    Layout.alignment: Qt.AlignHCenter
                }

                NowPlayingLabel {
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    horizontalAlignment: Qt.AlignHCenter
                    systemTray: true
                }

                RowLayout {
                    PlayButton {
                        systemTray: true
                        systemTrayMenu: menu
                    }

                    MuteButton {
                        systemTray: true
                        systemTrayMenu: menu
                    }

                    VolumeSlider {
                    }
                }
            }
        }

        MenuSeparator {
        }

        MenuItem {
            text: qsTr("Show Main Window")

            onTriggered: {
                window.applicationWindow.show();
                window.applicationWindow.requestActivate();
            }
        }

        MenuSeparator {
        }

        MenuItem {
            text: qsTr("Quit Radio")

            onTriggered: {
                Qt.quit();
            }
        }

        MenuSeparator {
        }

        /*
         * this button should probably always exist because when you click on
         * the application window with the menu open, the menu doesn't close;
         * it's just yet another bug Qt doesn't want to fix (QTBUG-33481)
         */
        MenuItem {
            text: qsTr("Hide Menu")
        }
    }
}
