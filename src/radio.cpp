#include "radio.h"
#include <QApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QMessageBox>
#include <QNetworkReply>
#include <QScrollBar>

void RadioStationsModel::setRadioStations(const QList<QJsonObject> &radioStations)
{
    beginResetModel();

    m_radioStations = radioStations;
    m_radioStationCount = 0;

    endResetModel();
}

QVariant RadioStationsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    const int row = index.row();

    if (row >= m_radioStations.size() or row < 0)
    {
        return QVariant();
    }

    switch (role)
    {
        case Qt::BackgroundRole:
        {
            return (row % 2) ? Qt::transparent : QColor(0xAA, 0x00, 0xFF, 25);
        }
        case Qt::DisplayRole:
        {
            return m_radioStations[row]["displayText"];
        }
        case Qt::UserRole:
        {
            return m_radioStations[row];
        }
        default:
        {
            return QVariant();
        }
    }
}

bool RadioStationsModel::canFetchMore(const QModelIndex &parent) const
{
    return (parent.isValid()) ? false : (m_radioStationCount < m_radioStations.size());
}

int RadioStationsModel::rowCount(const QModelIndex &parent) const
{
    return (parent.isValid()) ? 0 : m_radioStationCount;
}

void RadioStationsModel::fetchMore(const QModelIndex &parent)
{
    if (parent.isValid())
    {
        return;
    }

    const int itemsToFetch = qMin(3, m_radioStations.size() - m_radioStationCount);

    if (itemsToFetch <= 0)
    {
        return;
    }

    beginInsertRows(QModelIndex(), m_radioStationCount, m_radioStationCount + itemsToFetch - 1);

    m_radioStationCount += itemsToFetch;

    endInsertRows();
}

MuteUnmuteButton::MuteUnmuteButton(Radio *radio) : m_radio(radio)
{
    connect(this, &MuteUnmuteButton::clicked, this,
            [this]
            {
                m_radio->audioOutput()->setMuted(!m_radio->audioOutput()->isMuted());
            });

    setIcon(QIcon(":/normal/muteIcon"));
    setToolTip("Mute");
}

void MuteUnmuteButton::setMuted(const bool &isMuted)
{
    m_isMuted = isMuted;

    setIcon(QIcon(
        QString(":/%0/%1").arg((underMouse()) ? "hovered" : ((m_isMuted) ? "disabled" : "normal"),
                               (m_isMuted) ? "unmuteIcon" : "muteIcon")));
    m_radio->volumeSlider()->setVisuallyDisabled(m_isMuted);
    setToolTip((m_isMuted) ? "Unmute" : "Mute");

    setProperty("isMuted", m_isMuted);
    style()->polish(this);
}

void MuteUnmuteButton::enterEvent(QEnterEvent *)
{
    if (isEnabled())
    {
        setIcon(QIcon(QString(":/hovered/%0").arg((m_isMuted) ? "unmuteIcon" : "muteIcon")));
    }
}

void MuteUnmuteButton::leaveEvent(QEvent *)
{
    if (isEnabled())
    {
        setIcon(QIcon(QString(":/%0/%1").arg((m_isMuted) ? "disabled" : "normal",
                                             (m_isMuted) ? "unmuteIcon" : "muteIcon")));
    }
}

PlayStopButton::PlayStopButton(Radio *radio) : m_radio(radio)
{
    connect(this, &PlayStopButton::clicked, this,
            [this]
            {
                if (m_isPlaying)
                {
                    m_radio->mediaPlayer()->stop();
                }
                else
                {
                    m_radio->restartPlayback();
                }
            });

    setIcon(QIcon(":/normal/playIcon"));
    setDisabled(true);
}

void PlayStopButton::setPlaying(const bool &isPlaying)
{
    m_isPlaying = isPlaying;

    setIcon(QIcon(QString(":/%0/%1").arg((underMouse()) ? "hovered" : "normal",
                                         (m_isPlaying) ? "stopIcon" : "playIcon")));
    setToolTip((m_isPlaying) ? "Stop" : "Play");
}

void PlayStopButton::enterEvent(QEnterEvent *)
{
    if (isEnabled())
    {
        setIcon(QIcon(QString(":/hovered/%0").arg((m_isPlaying) ? "stopIcon" : "playIcon")));
    }
}

void PlayStopButton::leaveEvent(QEvent *)
{
    if (isEnabled())
    {
        setIcon(QIcon(QString(":/normal/%0").arg((m_isPlaying) ? "stopIcon" : "playIcon")));
    }
}

bool PlayStopButton::isPlaying()
{
    return m_isPlaying;
}

VolumeSlider::VolumeSlider(Radio *radio, const bool &isForMenu)
    : QSlider(Qt::Horizontal), m_radio(radio)
{
    connect(this, &VolumeSlider::valueChanged, this,
            [this](const int &value)
            {
                m_radio->audioOutput()->setVolume(value / 100.);
                m_radio->audioOutput()->setMuted(!value);
                setToolTip(QString("%0%").arg(value));
            });

    setProperty("isVisuallyDisabled", false);
    setProperty("isForMenu", isForMenu);
    setToolTipDuration(60000);
    setRange(0, 100);
    setPageStep(2);
}

void VolumeSlider::setVisuallyDisabled(const bool &visuallyDisabled)
{
    m_isVisuallyDisabled = visuallyDisabled;

    emit visuallyDisabledChanged(m_isVisuallyDisabled);

    setProperty("isVisuallyDisabled", m_isVisuallyDisabled);
    style()->polish(this);
}

Radio::Radio()
{
    connect(
        m_searchButton, &QPushButton::clicked, this,
        [this]
        {
            m_searchResultsListView->setDisabled(true);
            m_searchButton->setDisabled(true);
            m_searchLine->setDisabled(true);

            m_searchResultsListViewModel->setRadioStations({{{"displayText", "Searching..."}}});

            QNetworkReply *reply = m_accessManager->get(QNetworkRequest(
                QUrl("https://radio.garden/api/search?q=" + m_searchLine->text().trimmed())));

            connect(
                reply, &QNetworkReply::finished, this,
                [reply, this]
                {
                    m_searchButton->setDisabled(false);
                    m_searchLine->setDisabled(false);

                    if (reply->error())
                    {
                        m_searchResultsListViewModel->setRadioStations(
                            {{{"displayText", "Error."}}});

                        return (void)QMessageBox::critical(
                            this, "Search Error",
                            QString("[%0] " + reply->errorString()).arg(reply->error()));
                    }

                    QJsonParseError parseError;
                    const QJsonArray hits =
                        QJsonDocument::fromJson(reply->readAll(), &parseError)["hits"]["hits"]
                            .toArray();

                    if (parseError.error)
                    {
                        m_searchResultsListViewModel->setRadioStations(
                            {{{"displayText", "Error."}}});

                        return (void)QMessageBox::critical(
                            this, "Search Results Parse Error",
                            QString("%0 (%1)").arg(parseError.errorString(), parseError.offset));
                    }

                    QList<QJsonObject> radioStations;

                    for (const QJsonValue &hit : hits)
                    {
                        if (hit["_source"]["type"] == "channel")
                        {
                            radioStations.append(
                                {{{{"url",
                                    QString("https://radio.garden/api/ara/content/listen/%0/"
                                            "channel.mp3")
                                        .arg(hit["_source"]["url"].toString().split("/").last())},
                                   {"displayText",
                                    QString("%0 — " + hit["_source"]["subtitle"].toString())
                                        .arg(hit["_source"]["title"].toString())},
                                   {"subTitle", hit["_source"]["subtitle"]},
                                   {"title", hit["_source"]["title"]}}}});
                        }
                    }

                    if (radioStations.isEmpty())
                    {
                        m_searchResultsListViewModel->setRadioStations(
                            {{{"displayText", "No results."}}});
                        m_searchResultsListView->setDisabled(true);
                    }
                    else
                    {
                        m_searchResultsListViewModel->setRadioStations(radioStations);
                        m_searchResultsListView->setDisabled(false);
                    }

                    m_searchResultsListView->horizontalScrollBar()->setValue(0);
                    m_searchResultsListView->verticalScrollBar()->setValue(0);
                });
        });
    connect(m_mediaPlayer, &QMediaPlayer::mediaStatusChanged, this,
            [this](const QMediaPlayer::MediaStatus &status)
            {
                switch (status)
                {
                    case QMediaPlayer::LoadingMedia:
                    {
                        setWindowTitle("Radio - Loading...");

                        break;
                    }
                    case QMediaPlayer::LoadedMedia:
                    {
                        setWindowTitle("Radio - Loaded");

                        break;
                    }
                    case QMediaPlayer::StalledMedia:
                    {
                        setWindowTitle("Radio - Stalled");
                        m_timesInterrupted++;

                        if (m_timesInterrupted > 4)
                        {
                            m_timesInterrupted = 0;
                            restartPlayback();
                        }
                        else
                        {
                            QTimer::singleShot(500, this,
                                               [this]
                                               {
                                                   if (m_mediaPlayer->mediaStatus() ==
                                                       QMediaPlayer::StalledMedia)
                                                   {
                                                       restartPlayback();
                                                   }
                                               });
                        }

                        break;
                    }
                    case QMediaPlayer::BufferingMedia:
                    {
                        setWindowTitle("Radio - Buffering...");

                        break;
                    }
                    case QMediaPlayer::BufferedMedia:
                    {
                        setWindowTitle("Radio - Buffered");

                        break;
                    }
                    case QMediaPlayer::InvalidMedia:
                    {
                        setWindowTitle("Radio - Invalid Media");

                        break;
                    }
                    default:
                    {
                        setWindowTitle("Radio - Stopped");
                    }
                }
            });
    connect(m_searchResultsListView, &QListView::doubleClicked, this,
            [this](const QModelIndex &index)
            {
                const QJsonObject stationData = index.data(Qt::UserRole).toJsonObject();

                if (stationData["url"] == m_currentSourceOriginal)
                {
                    return m_playStopButton->click();
                }

                QNetworkReply *reply =
                    m_accessManager->get(QNetworkRequest(QUrl(stationData["url"].toString())));

                connect(reply, &QNetworkReply::redirected, reply,
                        [this, stationData](const QUrl &url)
                        {
                            m_nowPlayingLabel->setText(
                                QString("<a href=\"%0\">%1 [%2]</a>")
                                    .arg(url.url(), stationData["title"].toString(),
                                         stationData["subTitle"].toString()));

                            m_currentSourceOriginal = stationData["url"].toString();
                            m_currentSourceResolved = url;

                            restartPlayback();
                        });
                connect(reply, &QNetworkReply::errorOccurred, this,
                        [this, reply]
                        {
                            QMessageBox::critical(
                                this, "Error",
                                QString("[%0] " + reply->errorString()).arg(reply->error()));
                        });
            });
    connect(m_mediaPlayer, &QMediaPlayer::errorOccurred, this,
            [this](const QMediaPlayer::Error &error)
            {
                QMessageBox::critical(this, "Playback Error",
                                      QString("[%0] " + m_mediaPlayer->errorString()).arg(error));
            });
    connect(m_searchLine, &QLineEdit::textChanged, this,
            [this](const QString &text)
            {
                m_searchButton->setDisabled(text.trimmed().isEmpty());
                m_searchLine->style()->polish(m_searchLine);
            });
    connect(m_mediaPlayer, &QMediaPlayer::playbackStateChanged, this,
            [this](const QMediaPlayer::PlaybackState &state)
            {
                m_playStopButton->setPlaying(state == QMediaPlayer::PlayingState);
            });
    connect(m_audioOutput, &QAudioOutput::volumeChanged, m_volumeSlider,
            [this](const float &volume)
            {
                m_volumeSlider->setValue(qRound(volume * 100));
            });
    connect(m_frequentInterruptionDetectionTimer, &QTimer::timeout, this,
            [this]
            {
                m_timesInterrupted = 0;
            });
    connect(m_audioOutput, &QAudioOutput::mutedChanged, m_muteUnmuteButton,
            &MuteUnmuteButton::setMuted);
    connect(m_searchLine, &QLineEdit::returnPressed, m_searchButton, &QPushButton::click);

    m_searchResultsListViewModel->setRadioStations(
        {{{"displayText", "Start searching for stations."}}});
    m_accessManager->setRedirectPolicy(QNetworkRequest::UserVerifiedRedirectPolicy);
    m_searchResultsListView->setVerticalScrollMode(QListView::ScrollPerPixel);
    m_nowPlayingLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    m_searchResultsListView->setModel(m_searchResultsListViewModel);
    m_searchLine->setPlaceholderText("Search for a station");
    m_frequentInterruptionDetectionTimer->start(3000);
    m_nowPlayingLabel->setAlignment(Qt::AlignCenter);
    m_mediaPlayer->setAudioOutput(m_audioOutput);
    m_accessManager->setAutoDeleteReplies(true);
    m_searchResultsListView->setDisabled(true);
    m_separator->setFrameShape(QFrame::HLine);
    m_nowPlayingLabel->setWordWrap(true);
    m_searchButton->setDisabled(true);
    m_volumeSlider->setValue(100);

    m_layout->addWidget(m_nowPlayingLabel, 0, 0, 1, 3);
    m_layout->addWidget(m_playStopButton, 1, 0);
    m_layout->addWidget(m_muteUnmuteButton, 1, 1);
    m_layout->addWidget(m_volumeSlider, 1, 2);
    m_layout->addWidget(m_separator, 2, 0, 1, 3);
    m_layout->addWidget(m_searchLine, 3, 0, 1, 3);
    m_layout->addWidget(m_searchButton, 4, 0, 1, 3);
    m_layout->addWidget(m_searchResultsListView, 5, 0, 1, 3);

    setWindowTitle("Radio - Stopped");
    show();
}

MuteUnmuteButton *Radio::muteUnmuteButton()
{
    return m_muteUnmuteButton;
}

PlayStopButton *Radio::playStopButton()
{
    return m_playStopButton;
}

void Radio::closeEvent(QCloseEvent *)

{
    if (!m_playStopButton->isPlaying())
    {
        qApp->quit();
    }
}

VolumeSlider *Radio::volumeSlider()
{
    return m_volumeSlider;
}

void Radio::showEvent(QShowEvent *)
{
    m_searchLine->setFocus();
}

QAudioOutput *Radio::audioOutput()
{
    return m_audioOutput;
}

QMediaPlayer *Radio::mediaPlayer()
{
    return m_mediaPlayer;
}

const QUrl Radio::currentSource()
{
    return m_currentSourceResolved;
}

void Radio::restartPlayback()
{
    m_playStopButton->setDisabled(true);
    m_mediaPlayer->setSource(QUrl());

    QTimer::singleShot(10, this,
                       [this]
                       {
                           m_mediaPlayer->setSource(m_currentSourceResolved);
                           m_mediaPlayer->play();

                           m_playStopButton->setDisabled(false);
                       });
}