#include "equalizer.h"
#include "player.h"
#include "utilities.h"

Q_LOGGING_CATEGORY(radio_equalizer, "radio.equalizer")

Equalizer::Equalizer()
{
    applySettingsFromPreset(0);
}

Equalizer *Equalizer::qmlInstance(QQmlEngine *, QJSEngine *)
{
    static Equalizer *instance = new Equalizer;

    return instance;
}

void Equalizer::applySettingsFromPreset(const unsigned &presetIndex)
{
    const QString presetName = libvlc_audio_equalizer_get_preset_name(presetIndex);

    qCDebug(radio_equalizer) << "applying settings from preset with index" << presetIndex
                             << "with name" << presetName << "to equalizer";

    libvlc_equalizer_t *equalizerFromPreset = libvlc_audio_equalizer_new_from_preset(presetIndex);

    if (!equalizerFromPreset)
    {
        reportError(
            QString("Failed to apply settings from preset \"%0\" to equalizer.").arg(presetName),
            QString(
                "failed to apply settings from preset with index %0 with name \"%1\" to equalizer")
                .arg(QString::number(presetIndex), presetName));

        return;
    }

    const unsigned bandCount = libvlc_audio_equalizer_get_band_count();

    for (unsigned i = 0; i < bandCount; ++i)
    {
        const float newAmp = libvlc_audio_equalizer_get_amp_at_index(equalizerFromPreset, i);

        if (!m_equalizer || newAmp != libvlc_audio_equalizer_get_amp_at_index(m_equalizer, i))
        {
            emit ampChanged(i, newAmp);
        }
    }

    const float newPreamp = libvlc_audio_equalizer_get_preamp(equalizerFromPreset);

    if (newPreamp != preamp())
    {
        emit preampChanged(newPreamp);
    }

    libvlc_audio_equalizer_release(m_equalizer);

    m_equalizer = equalizerFromPreset;

    applyToMediaPlayer();
}

bool Equalizer::applyToMediaPlayer()
{
    return applyToMediaPlayer(m_enabled);
}

void Equalizer::setAmpAtIndex(const unsigned &index, const float &amp)
{
    const float currentAmp = libvlc_audio_equalizer_get_amp_at_index(m_equalizer, index);

    if (amp == currentAmp)
    {
        return;
    }

    qCDebug(radio_equalizer).nospace() << "setting amp at index " << index << " to " << amp << "dB";

    if (libvlc_audio_equalizer_set_amp_at_index(m_equalizer, amp, index) != -1)
    {
        if (!applyToMediaPlayer())
        {
            emit ampChanged(index, currentAmp);
        }

        return;
    }

    const float bandFrequency = libvlc_audio_equalizer_get_band_frequency(index);
    const QString stringifiedAmp = QString::number(amp, 'f', 1);

    reportError(
        QString("Failed to set amp for the %0 %1Hz band to %2dB.")
            .arg(QString::number((bandFrequency >= 1000) ? (bandFrequency / 1000) : bandFrequency,
                                 'f', 0),
                 (bandFrequency >= 1000) ? "k" : QString(), stringifiedAmp),
        QString("failed to set amp at index %0 to %1dB")
            .arg(QString::number(index), stringifiedAmp));

    emit ampChanged(index, currentAmp);
}

void Equalizer::setPreamp(const float &preamp)
{
    const float currentPreamp = this->preamp();

    if (preamp == currentPreamp)
    {
        return;
    }

    qCDebug(radio_equalizer).nospace() << "setting preamp to " << preamp << "dB";

    if (libvlc_audio_equalizer_set_preamp(m_equalizer, preamp) != -1)
    {
        if (!applyToMediaPlayer())
        {
            emit preampChanged(currentPreamp);
        }

        return;
    }

    const QString stringifiedPreamp = QString::number(preamp, 'f', 1);

    reportError(QString("Failed to set preamp to %0dB.").arg(stringifiedPreamp),
                QString("failed to set preamp to %0dB").arg(stringifiedPreamp));

    emit preampChanged(currentPreamp);
}

void Equalizer::setEnabled(const bool &enabled)
{
    if (enabled == m_enabled)
    {
        return;
    }

    qCDebug(radio_equalizer) << ((enabled) ? "enabling" : "disabling") << "the equalizer";

    if (applyToMediaPlayer(enabled))
    {
        m_enabled = enabled;
    }

    emit enabledChanged(m_enabled);
}

void Equalizer::reportError(const QString &messageDialogMessage, const QString &logMessage)
{
    const QString libVlcErrorMessage = libvlc_errmsg();

    qCCritical(radio_equalizer).nospace().noquote()
        << logMessage
        << ((libVlcErrorMessage.isEmpty()) ? QString()
                                           : QString(": \"%0\"").arg(libVlcErrorMessage));

    Utilities::requestMessageDialog("Equalizer Error", messageDialogMessage, libVlcErrorMessage);
}

bool Equalizer::applyToMediaPlayer(const bool &enabled)
{
    qCDebug(radio_equalizer) << "applying new equalizer settings to media player";

    if (Player::setEqualizer((enabled) ? m_equalizer : NULL))
    {
        return true;
    }

    reportError("Failed to apply new equalizer settings to media player.",
                "failed to apply new equalizer settings to media player");

    return false;
}

const QStringList Equalizer::presetNames()
{
    QStringList presetNames;

    const unsigned presetCount = libvlc_audio_equalizer_get_preset_count();

    for (unsigned i = 0; i < presetCount; ++i)
    {
        presetNames << libvlc_audio_equalizer_get_preset_name(i);
    }

    return presetNames;
}

const QList<EqualizerBand> Equalizer::bands()
{
    QList<EqualizerBand> bands;

    const unsigned bandCount = libvlc_audio_equalizer_get_band_count();

    for (unsigned i = 0; i < bandCount; ++i)
    {
        EqualizerBand band;

        band.frequency = libvlc_audio_equalizer_get_band_frequency(i);
        band.amp = libvlc_audio_equalizer_get_amp_at_index(m_equalizer, i);
        band.index = i;

        bands << band;
    }

    return bands;
}

const float Equalizer::preamp()
{
    return (m_equalizer) ? libvlc_audio_equalizer_get_preamp(m_equalizer) : 0.;
}
