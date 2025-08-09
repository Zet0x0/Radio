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

        margins: 0 // NOTE: values above 0 make the menu have a stroke and shrink to 0 pixels

        onClosed: {
            window.hide();
        }

        Control {
            enabled: window.applicationWindow.enabled

            contentItem: ColumnLayout {
                StationImage {
                    Layout.alignment: Qt.AlignHCenter
                }

                Control {
                    Layout.preferredWidth: controlLayout.width

                    contentItem: NowPlayingLabel {
                        systemTray: true
                        width: Math.min(implicitWidth, parent.width)
                        x: Math.floor((parent.width - width) / 2)
                    }
                }

                RowLayout {
                    id: controlLayout

                    ShazamNowPlayingButton {
                        systemTray: true
                        systemTrayMenu: menu
                    }

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

        Action {
            text: qsTr("Show Main Window")

            onTriggered: {
                window.applicationWindow.show();
                window.applicationWindow.requestActivate();
            }
        }

        MenuSeparator {
        }

        Action {
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
        Action {
            text: qsTr("Hide Menu")
        }
    }
}
