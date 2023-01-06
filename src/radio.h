#pragma once

#include <QAudioDevice>
#include <QAudioOutput>
#include <QGridLayout>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QMediaDevices>
#include <QMediaPlayer>
#include <QNetworkAccessManager>
#include <QPushButton>
#include <QTimer>
#include <QToolButton>

class Radio;

class RadioStationsModel : public QAbstractListModel
{
private:
    QList<QJsonObject> m_radioStations;
    int m_radioStationCount = 0;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool canFetchMore(const QModelIndex &parent) const override;
    void fetchMore(const QModelIndex &parent) override;

public:
    void setRadioStations(const QList<QJsonObject> &radioStations);
};

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
private:
    QMediaPlayer *m_mediaPlayer = new QMediaPlayer(this);
    QAudioOutput *m_audioOutput =
        new QAudioOutput(QMediaDevices::defaultAudioOutput(), m_mediaPlayer);
    QNetworkAccessManager *m_accessManager = new QNetworkAccessManager(this);

    RadioStationsModel *m_searchResultsListViewModel = new RadioStationsModel;
    MuteUnmuteButton *m_muteUnmuteButton = new MuteUnmuteButton(this);
    QLabel *m_nowPlayingLabel = new QLabel("No station selected.");
    PlayStopButton *m_playStopButton = new PlayStopButton(this);
    QPushButton *m_searchButton = new QPushButton("Search");
    VolumeSlider *m_volumeSlider = new VolumeSlider(this);
    QListView *m_searchResultsListView = new QListView;
    QGridLayout *m_layout = new QGridLayout(this);
    QLineEdit *m_searchLine = new QLineEdit;
    QFrame *m_separator = new QFrame;

    QTimer *m_frequentInterruptionDetectionTimer = new QTimer(this);
    int m_timesInterrupted = 0;

    QString m_currentSourceOriginal;
    QUrl m_currentSourceResolved;

    void closeEvent(QCloseEvent *);
    void showEvent(QShowEvent *);

public:
    Radio();

    MuteUnmuteButton *muteUnmuteButton();
    PlayStopButton *playStopButton();
    VolumeSlider *volumeSlider();

    QAudioOutput *audioOutput();
    QMediaPlayer *mediaPlayer();
    const QUrl currentSource();

    void restartPlayback();
};