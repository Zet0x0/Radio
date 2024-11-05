#pragma once

#include <QLoggingCategory>
#include <QQmlEngine>
#include <vlc/vlc.h>

Q_DECLARE_LOGGING_CATEGORY(radio_equalizer)

struct EqualizerBand
{
    Q_GADGET

    Q_PROPERTY(float frequency MEMBER frequency FINAL)
    Q_PROPERTY(float amp MEMBER amp FINAL)
    Q_PROPERTY(unsigned index MEMBER index FINAL)

public:
    float frequency;
    float amp;
    unsigned index;
};

class Equalizer : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool enabled MEMBER m_enabled WRITE setEnabled NOTIFY enabledChanged FINAL)

    Q_PROPERTY(float preamp READ preamp WRITE setPreamp NOTIFY preampChanged FINAL)

public slots:
    void setAmpAtIndex(const unsigned &index, const float &amp);
    void setPreamp(const float &);

    void applySettingsFromPreset(const unsigned &presetIndex);

    void setEnabled(const bool &);

private:
    libvlc_equalizer_t *m_equalizer{};
    bool m_enabled = false;

    Equalizer();

    void reportError(const QString &messageDialogMessage, const QString &logMessage);

    bool applyToMediaPlayer(const bool &enabled);
    bool applyToMediaPlayer();

signals:
    void ampChanged(const unsigned &index, const float &amp);
    void preampChanged(const float &);

    void enabledChanged(const bool &);

public:
    static Equalizer *qmlInstance(QQmlEngine *, QJSEngine *);

    Q_INVOKABLE const QList<EqualizerBand> bands();
    Q_INVOKABLE const float preamp();

    Q_INVOKABLE const QStringList presetNames();
};

Q_DECLARE_METATYPE(EqualizerBand)
