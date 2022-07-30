#include "radio.h"
#include <QApplication>
#include <QFontDatabase>
#include <QMenu>
#include <QPainter>
#include <QProxyStyle>
#include <QSystemTrayIcon>
#include <QWidgetAction>

class ApplicationStyle : public QProxyStyle
{
private:
    void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter,
                       const QWidget *widget) const
    {
        if (element != QStyle::PE_FrameFocusRect)
        {
            QProxyStyle::drawPrimitive(element, option, painter, widget);
        }
    }

    QPixmap generatedIconPixmap(QIcon::Mode mode, const QPixmap &pixmap,
                                const QStyleOption *option) const
    {
        if (mode != QIcon::Disabled)
        {
            return QProxyStyle::generatedIconPixmap(mode, pixmap, option);
        }

        QPixmap newPixmap(pixmap);
        QPainter painter(&newPixmap);

        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(newPixmap.rect(), QColor(0x55, 0x00, 0x80));
        painter.end();

        return newPixmap;
    }

public:
    ApplicationStyle() : QProxyStyle("Fusion")
    {
    }
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QFontDatabase::addApplicationFont(":/OCR-A.ttf");

    app.setWindowIcon(QIcon(":/normal/applicationIcon"));
    app.setEffectEnabled(Qt::UI_FadeTooltip);
    app.setQuitOnLastWindowClosed(false);

    QPalette appPalette = app.palette();

    appPalette.setColor(QPalette::Link, QColor(0xAA, 0x00, 0xFF));
    app.setPalette(appPalette);

    app.setStyle(new ApplicationStyle);
    app.setStyleSheet(
        "QSlider[isVisuallyDisabled=true]::groove:horizontal, "
        "QSlider[isVisuallyDisabled=true]::handle:horizontal, QScrollBar { background: #550080; }"
        "* { selection-background-color: #a0f; selection-color: white; background: black; font: "
        "10pt \"OCR-A\"; color: #a0f; }"
        "QPushButton:disabled, QToolButton:disabled, QLineEdit:disabled { border: 1 solid #550080; "
        "color: #550080; }"
        "QMenu::item:selected, QPushButton:hover, QToolButton:hover { color: white; background: "
        "#a0f; }"
        "QToolButton[isMuted=true]:hover, QToolButton, QListView, QMenu { border: 1 solid #a0f; }"
        "QSlider[isVisuallyDisabled=false]::add-page:horizontal { background: #550080; }"
        "QFrame[frameShape=\"HLine\"] { background: #a0f; max-height: 1; border: none; }"
        "QSlider[isVisuallyDisabled=false]::sub-page:horizontal { background: #a0f; }"
        "QToolButton[isMuted=true], QListView:disabled { border: 1 solid #550080; }"
        "QSlider::handle:horizontal { background: #a0f; margin: -8 0; width: 6; }"
        "QScrollBar::add-line, QScrollBar::sub-line { height: 0; width: 0; }"
        "QScrollBar:horizontal { margin-top: 1; min-width: 32; height: 6; }"
        "QScrollBar:vertical { margin-left: 1; min-height: 32; width: 6; }"
        "QListView::item:disabled { color: #550080; background: black; }"
        "QMenu::item:disabled, QLineEdit[text=\"\"] { color: #550080; }"
        "QSlider::groove:horizontal { background: #a0f; height: 1; }"
        "QLineEdit { border: 1 solid #a0f; padding: 0 -2 1 -1; }"
        "QScrollBar::handle:disabled { background: #550080; }"
        "QPushButton { border: 1 solid #a0f; padding: 6 32; }"
        "QMenu::separator { background: #a0f; height: 1; }"
        "QToolTip { border: 1 solid #a0f; padding: 1; }"
        "QSlider[isForMenu=true] { margin: 2 1 0 1; }"
        "QScrollBar:disabled { background: black; }"
        "QScrollBar::handle { background: #a0f; }"
        "QToolButton { padding: 0 -1 -1 0; }"
        "QMenu::item { margin: 1;}"
        "QListView { padding: 1; }");

    QSystemTrayIcon *systemTray = new QSystemTrayIcon(app.windowIcon());
    QMenu *systemTrayMenu = new QMenu;
    Radio *radio = new Radio;

    QAction *mediaStatusAction = systemTrayMenu->addAction("Stopped");
    systemTrayMenu->addSeparator();

    VolumeSlider *volumeSlider = new VolumeSlider(radio, true);
    QWidgetAction *volumeSliderAction = new QWidgetAction(systemTrayMenu);

    volumeSliderAction->setDefaultWidget(volumeSlider);

    systemTrayMenu->addAction(volumeSliderAction);
    QAction *muteUnmuteAction =
        systemTrayMenu->addAction("Mute", radio->muteUnmuteButton(), &QToolButton::click);

    systemTrayMenu->addSeparator();
    QAction *playStopAction =
        systemTrayMenu->addAction("Play", radio->playStopButton(), &QToolButton::click);
    systemTrayMenu->addSeparator();
    systemTrayMenu->addAction("Quit", &app, &QApplication::quit);

    QObject::connect(radio->mediaPlayer(), &QMediaPlayer::playbackStateChanged, &app,
                     [playStopAction](const QMediaPlayer::PlaybackState &state)
                     {
                         playStopAction->setText((state == QMediaPlayer::PlayingState) ? "Stop"
                                                                                       : "Play");
                         playStopAction->setDisabled(false);
                     });
    QObject::connect(systemTray, &QSystemTrayIcon::activated, radio,
                     [radio](const QSystemTrayIcon::ActivationReason &reason)
                     {
                         if (reason == QSystemTrayIcon::Trigger)
                         {
                             (radio->isVisible()) ? radio->activateWindow() : radio->show();
                         }
                     });
    QObject::connect(radio, &Radio::windowTitleChanged, systemTray,
                     [systemTray, mediaStatusAction](const QString &text)
                     {
                         mediaStatusAction->setText(text.split(" - ", Qt::SkipEmptyParts).last());
                         systemTray->setToolTip(text);
                     });
    QObject::connect(radio->audioOutput(), &QAudioOutput::mutedChanged, &app,
                     [muteUnmuteAction](const bool &muted)
                     {
                         muteUnmuteAction->setText((muted) ? "Unmute" : "Mute");
                     });
    QObject::connect(radio->volumeSlider(), &VolumeSlider::visuallyDisabledChanged, volumeSlider,
                     &VolumeSlider::setVisuallyDisabled);
    QObject::connect(radio->volumeSlider(), &VolumeSlider::valueChanged, volumeSlider,
                     &VolumeSlider::setValue);
    QObject::connect(&app, &QApplication::aboutToQuit, systemTray, &QSystemTrayIcon::hide);

    systemTray->setContextMenu(systemTrayMenu);
    systemTray->setToolTip("Radio - Stopped");
    mediaStatusAction->setDisabled(true);
    playStopAction->setDisabled(true);
    volumeSlider->setValue(100);
    systemTray->show();

    return app.exec();
}