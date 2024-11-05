import QtQuick

import QtQuick.Controls
import QtQuick.Layouts

import Radio.Equalizer

Pane {
    id: equalizerBand

    property alias amp: ampSlider.value
    property double frequency: 0.
    property int index: -1

    property string text

    ColumnLayout {
        anchors.fill: parent

        Slider {
            id: ampSlider

            implicitHeight: implicitWidth * 5

            orientation: Qt.Vertical

            secondaryColor: "#a0f"

            wheelStepSize: .3
            stepSize: .1

            from: -20.
            to: 20.

            onValueChanged: {
                const fixedValue = value.toFixed(1)

                if (equalizerBand.index === -1) {
                    Equalizer.setPreamp(fixedValue)
                } else {
                    Equalizer.setAmpAtIndex(equalizerBand.index, fixedValue)
                }
            }

            Layout.fillWidth: true
        }

        Label {
            text: {
                const frequency = equalizerBand.frequency

                return equalizerBand.text
                        || `${(frequency >= 1000) ? (frequency / 1000) : frequency.toFixed(
                                                        )} ${(frequency >= 1000) ? "k" : ""}Hz`
            }

            horizontalAlignment: Label.AlignHCenter

            Layout.fillWidth: true
        }

        Label {
            text: {
                const ampValue = ampSlider.value.toFixed(1)

                return `${(ampValue == -0.) ? (0).toFixed(1) : ampValue} dB`
            }

            horizontalAlignment: Label.AlignHCenter

            fontSizeMultiplier: .75

            Layout.fillWidth: true
        }
    }
}
