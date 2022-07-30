#pragma once

#include <QAudioDevice>
#include <QAudioOutput>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QMediaDevices>
#include <QMediaPlayer>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QStandardItemModel>
#include <QTimer>
#include <QToolButton>

QT_FORWARD_DECLARE_CLASS(Radio);

class MuteUnmuteButton : public QToolButton
{
    Q_OBJECT

public slots:
    void setMuted(const bool &);

private:
    bool m_isMuted = false;
    Radio *m_radio;

    void enterEvent(QEnterEvent *);
    void leaveEvent(QEvent *);

public:
    MuteUnmuteButton(Radio *);
};

class VolumeSlider : public QSlider
{
    Q_OBJECT

public slots:
    void setVisuallyDisabled(const bool &);

private:
    bool m_isVisuallyDisabled = false;
    Radio *m_radio;

signals:
    void visuallyDisabledChanged(const bool &);

public:
    VolumeSlider(Radio *, const bool &isForMenu = false);
};

class Radio : public QWidget
{
    class PlayStopButton : public QToolButton
    {
    private:
        bool m_isPlaying = false;
        Radio *m_radio;

        void enterEvent(QEnterEvent *);
        void leaveEvent(QEvent *);

    public:
        PlayStopButton(Radio *);

        void setPlaying(const bool &);
        bool isPlaying();
    };

private:
    QAudioOutput *m_audioOutput = new QAudioOutput(QMediaDevices::defaultAudioOutput());
    QNetworkAccessManager *m_accessManager = new QNetworkAccessManager;
    QMediaPlayer *m_mediaPlayer = new QMediaPlayer;

    QStandardItemModel *m_searchResultsListViewModel = new QStandardItemModel;
    MuteUnmuteButton *m_muteUnmuteButton = new MuteUnmuteButton(this);
    QLabel *m_nowPlayingLabel = new QLabel("No station selected.");
    PlayStopButton *m_playStopButton = new PlayStopButton(this);
    QPushButton *m_searchButton = new QPushButton("Search");
    QListView *m_searchResultsListView = new QListView;
    QGridLayout *m_layout = new QGridLayout(this);
    QLineEdit *m_searchLine = new QLineEdit;
    QFrame *m_separator = new QFrame;

    QTimer *m_frequentInterruptionDetectionTimer = new QTimer;
    int m_timesInterrupted = 0;

    QString m_currentSourceOriginal;
    QUrl m_currentSourceResolved;

    void closeEvent(QCloseEvent *);

public:
    Radio();

    MuteUnmuteButton *muteUnmuteButton();
    PlayStopButton *playStopButton();
    VolumeSlider *volumeSlider();

    QAudioOutput *audioOutput();
    QMediaPlayer *mediaPlayer();
    const QUrl currentSource();

private:
    VolumeSlider *m_volumeSlider = new VolumeSlider(this);
};