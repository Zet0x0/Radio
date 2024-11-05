pragma Singleton

import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import "../components"
import "../"

import Radio.Equalizer

Dialog {
    contentItem: GridLayout {
        columns: 4
        rows: 3

        Label {
            background: Rectangle {
                color: "#a0f"
            }

            text: "Click to show an important warning"

            horizontalAlignment: Label.AlignHCenter

            font.bold: true

            color: "#fff"

            padding: 5

            Layout.fillWidth: true

            Layout.columnSpan: 4

            MouseArea {
                anchors.fill: parent

                onClicked: MessageDialog.show(
                               "Important Equalizer Warning", Utilities.dedent(
                                   `Due to some internal bug, you may randomly and suddenly encounter rapidly increasing volume, making the audio distorted and very loud.\n
                                   If you do encounter this, simply stop the playback, wait a second, and restart it back. If that didn't help at first, keep retrying until you get it fixed.\n
                                   There's nothing I can do about this.`), "")
            }
        }

        CheckBox {
            checked: Equalizer.enabled

            text: "Enable"

            onToggled: Equalizer.setEnabled(!Equalizer.enabled)
        }

        Item {
            Layout.fillWidth: true
        }

        Label {
            enabled: Equalizer.enabled

            text: "Preset:"
        }

        ComboBox {
            model: Equalizer.presetNames()

            enabled: Equalizer.enabled

            onActivated: index => {
                Equalizer.applySettingsFromPreset(index)
            }
        }

        RowLayout {
            enabled: Equalizer.enabled

            Layout.columnSpan: 4

            EqualizerBand {
                id: preampEqualizerBand

                amp: Equalizer.preamp

                text: "Preamp"
            }

            Item {
                implicitWidth: preampEqualizerBand.width / 4
            }

            Repeater {
                id: equalizerBandRepeater

                model: Equalizer.bands()

                EqualizerBand {
                    required property var modelData

                    implicitWidth: preampEqualizerBand.width

                    frequency: modelData.frequency
                    index: modelData.index
                    amp: modelData.amp
                }
            }
        }
    }

    parent: DialogMaster.defaultParent

    title: "Equalizer"

    Connections {
        function onAmpChanged(index, amp) {
            equalizerBandRepeater.itemAt(index).amp = amp
        }

        function onPreampChanged(preamp) {
            preampEqualizerBand.amp = preamp
        }

        target: Equalizer
    }
}
