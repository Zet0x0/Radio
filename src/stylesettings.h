#pragma once

/*

           ) (   (      (    (   (          (   (              (   (
  *   ) ( /( )\ ))\ )   )\ ) )\ ))\ )       )\ ))\ )     (     )\ ))\ )
` )  /( )\()|()/(()/(  (()/((()/(()/( (    (()/(()/(     )\   (()/(()/(
 ( )(_)|(_)\ /(_))(_))  /(_))/(_))(_)))\    /(_))(_)) ((((_)(  /(_))(_))
(_(_()) _((_|_))(_))   (_))_(_))(_)) ((_)  (_))(_))    )\ _ )\(_))(_))
|_   _|| || |_ _/ __|  | |_ |_ _| |  | __| |_ _/ __|   (_)_\(_) __/ __|
  | |  | __ || |\__ \  | __| | || |__| _|   | |\__ \    / _ \ \__ \__ \
  |_|  |_||_|___|___/  |_|  |___|____|___| |___|___/   /_/ \_\|___/___/

 */

#include "settingsbase.h"

#include <QColor>
#include <QFont>
#include <QQmlEngine>

class StyleSettings : public SettingsBase
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT

    // border
    /* border/width */ Q_PROPERTY(
        int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY
            borderWidthChanged FINAL)
    // ================================

    // controls
    /* controls/comboBox/indicator/padding */ Q_PROPERTY(
        int controlsComboBoxIndicatorPadding READ
            controlsComboBoxIndicatorPadding WRITE
                setControlsComboBoxIndicatorPadding NOTIFY
                    controlsComboBoxIndicatorPaddingChanged FINAL)
    /* controls/iconButton/padding */ Q_PROPERTY(
        int controlsIconButtonPadding READ controlsIconButtonPadding WRITE
            setControlsIconButtonPadding NOTIFY controlsIconButtonPaddingChanged
                FINAL)
    /* controls/itemDelegate/iconSize */ Q_PROPERTY(
        int controlsItemDelegateIconSize READ controlsItemDelegateIconSize WRITE
            setControlsItemDelegateIconSize NOTIFY
                controlsItemDelegateIconSizeChanged FINAL)
    /* controls/margins */ Q_PROPERTY(
        int controlsMargins READ controlsMargins WRITE setControlsMargins NOTIFY
            controlsMarginsChanged FINAL)
    /* controls/menuBarItem/iconSize */ Q_PROPERTY(
        int controlsMenuBarItemIconSize READ controlsMenuBarItemIconSize WRITE
            setControlsMenuBarItemIconSize NOTIFY
                controlsMenuBarItemIconSizeChanged FINAL)
    /* controls/menuItem/iconSize */ Q_PROPERTY(
        int controlsMenuItemIconSize READ controlsMenuItemIconSize WRITE
            setControlsMenuItemIconSize NOTIFY controlsMenuItemIconSizeChanged
                FINAL)
    /* controls/menu/overlap */ Q_PROPERTY(
        int controlsMenuOverlap READ controlsMenuOverlap WRITE
            setControlsMenuOverlap NOTIFY controlsMenuOverlapChanged FINAL)
    /* controls/padding */ Q_PROPERTY(
        int controlsPadding READ controlsPadding WRITE setControlsPadding NOTIFY
            controlsPaddingChanged FINAL)
    /* controls/scrollIndicator/opacity/active */ Q_PROPERTY(
        qreal controlsScrollIndicatorOpacityActive READ
            controlsScrollIndicatorOpacityActive WRITE
                setControlsScrollIndicatorOpacityActive NOTIFY
                    controlsScrollIndicatorOpacityActiveChanged FINAL)
    /* controls/scrollIndicator/opacity/inactive */ Q_PROPERTY(
        qreal controlsScrollIndicatorOpacityInactive READ
            controlsScrollIndicatorOpacityInactive WRITE
                setControlsScrollIndicatorOpacityInactive NOTIFY
                    controlsScrollIndicatorOpacityInactiveChanged FINAL)
    /* controls/scrollIndicator/padding */ Q_PROPERTY(
        int controlsScrollIndicatorPadding READ controlsScrollIndicatorPadding
            WRITE setControlsScrollIndicatorPadding NOTIFY
                controlsScrollIndicatorPaddingChanged FINAL)
    /* controls/scrollIndicator/pauseDuration */ Q_PROPERTY(
        int controlsScrollIndicatorPauseDuration READ
            controlsScrollIndicatorPauseDuration WRITE
                setControlsScrollIndicatorPauseDuration NOTIFY
                    controlsScrollIndicatorPauseDurationChanged FINAL)
    /* controls/scrollIndicator/size */ Q_PROPERTY(
        int controlsScrollIndicatorSize READ controlsScrollIndicatorSize WRITE
            setControlsScrollIndicatorSize NOTIFY
                controlsScrollIndicatorSizeChanged FINAL)
    /* controls/scrollIndicator/switchToInactiveDuration */ Q_PROPERTY(
        int controlsScrollIndicatorSwitchToInactiveDuration READ
            controlsScrollIndicatorSwitchToInactiveDuration WRITE
                setControlsScrollIndicatorSwitchToInactiveDuration NOTIFY
                    controlsScrollIndicatorSwitchToInactiveDurationChanged
                        FINAL)
    /* controls/separator/size */ Q_PROPERTY(
        int controlsSeparatorSize READ controlsSeparatorSize WRITE
            setControlsSeparatorSize NOTIFY controlsSeparatorSizeChanged FINAL)
    /* controls/slider/handle/height */ Q_PROPERTY(
        int controlsSliderHandleHeight READ controlsSliderHandleHeight WRITE
            setControlsSliderHandleHeight NOTIFY
                controlsSliderHandleHeightChanged FINAL)
    /* controls/slider/handle/width */ Q_PROPERTY(
        int controlsSliderHandleWidth READ controlsSliderHandleWidth WRITE
            setControlsSliderHandleWidth NOTIFY controlsSliderHandleWidthChanged
                FINAL)
    /* controls/slider/implicitHeight */ Q_PROPERTY(
        int controlsSliderImplicitHeight READ controlsSliderImplicitHeight WRITE
            setControlsSliderImplicitHeight NOTIFY
                controlsSliderImplicitHeightChanged FINAL)
    /* controls/slider/implicitWidth */ Q_PROPERTY(
        int controlsSliderImplicitWidth READ controlsSliderImplicitWidth WRITE
            setControlsSliderImplicitWidth NOTIFY
                controlsSliderImplicitWidthChanged FINAL)
    /* controls/spacing */ Q_PROPERTY(
        int controlsSpacing READ controlsSpacing WRITE setControlsSpacing NOTIFY
            controlsSpacingChanged FINAL)
    /* controls/stationImage/opacity/disabled */ Q_PROPERTY(
        qreal controlsStationImageOpacityDisabled READ
            controlsStationImageOpacityDisabled WRITE
                setControlsStationImageOpacityDisabled NOTIFY
                    controlsStationImageOpacityDisabledChanged FINAL)
    /* controls/stationImage/padding */ Q_PROPERTY(
        int controlsStationImagePadding READ controlsStationImagePadding WRITE
            setControlsStationImagePadding NOTIFY
                controlsStationImagePaddingChanged FINAL)
    /* controls/stationImage/size */ Q_PROPERTY(
        int controlsStationImageSize READ controlsStationImageSize WRITE
            setControlsStationImageSize NOTIFY controlsStationImageSizeChanged
                FINAL)
    /* controls/stationImage/stationLoadingIndicator/background/opacity */
    Q_PROPERTY(
        qreal controlsStationImageStationLoadingIndicatorBackgroundOpacity READ
            controlsStationImageStationLoadingIndicatorBackgroundOpacity WRITE
                setControlsStationImageStationLoadingIndicatorBackgroundOpacity
                    NOTIFY
                        controlsStationImageStationLoadingIndicatorBackgroundOpacityChanged
                            FINAL)
    /* controls/stationImage/stationLoadingIndicator/bounceBack */ Q_PROPERTY(
        bool controlsStationImageStationLoadingIndicatorBounceBack READ
            controlsStationImageStationLoadingIndicatorBounceBack WRITE
                setControlsStationImageStationLoadingIndicatorBounceBack NOTIFY
                    controlsStationImageStationLoadingIndicatorBounceBackChanged
                        FINAL)
    /* controls/stationImage/stationLoadingIndicator/frames */ Q_PROPERTY(
        QStringList controlsStationImageStationLoadingIndicatorFrames READ
            controlsStationImageStationLoadingIndicatorFrames WRITE
                setControlsStationImageStationLoadingIndicatorFrames NOTIFY
                    controlsStationImageStationLoadingIndicatorFramesChanged
                        FINAL)
    /* controls/stationImage/stationLoadingIndicator/interval */ Q_PROPERTY(
        int controlsStationImageStationLoadingIndicatorInterval READ
            controlsStationImageStationLoadingIndicatorInterval WRITE
                setControlsStationImageStationLoadingIndicatorInterval NOTIFY
                    controlsStationImageStationLoadingIndicatorIntervalChanged
                        FINAL)
    /* controls/topLayout/controlLayout/height */ Q_PROPERTY(
        int controlsTopLayoutControlLayoutHeight READ
            controlsTopLayoutControlLayoutHeight WRITE
                setControlsTopLayoutControlLayoutHeight NOTIFY
                    controlsTopLayoutControlLayoutHeightChanged FINAL)
    /* controls/volumeSlider/verticalPadding */ Q_PROPERTY(
        int controlsVolumeSliderVerticalPadding READ
            controlsVolumeSliderVerticalPadding WRITE
                setControlsVolumeSliderVerticalPadding NOTIFY
                    controlsVolumeSliderVerticalPaddingChanged FINAL)
    // ================================

    // dialogs
    /* dialogs/aboutDialog/maximumWidth */ Q_PROPERTY(
        int dialogsAboutDialogMaximumWidth READ dialogsAboutDialogMaximumWidth
            WRITE setDialogsAboutDialogMaximumWidth NOTIFY
                dialogsAboutDialogMaximumWidthChanged FINAL)
    /* dialogs/messageDialog/maximumWidth */ Q_PROPERTY(
        int dialogsMessageDialogMaximumWidth READ
            dialogsMessageDialogMaximumWidth WRITE
                setDialogsMessageDialogMaximumWidth NOTIFY
                    dialogsMessageDialogMaximumWidthChanged FINAL)
    /* dialogs/openLocationDialog/maximumWidth */ Q_PROPERTY(
        int dialogsOpenLocationDialogMaximumWidth READ
            dialogsOpenLocationDialogMaximumWidth WRITE
                setDialogsOpenLocationDialogMaximumWidth NOTIFY
                    dialogsOpenLocationDialogMaximumWidthChanged FINAL)
    // ================================

    // fonts
    /* fonts/application */ Q_PROPERTY(
        QFont fontsApplication READ fontsApplication WRITE setFontsApplication
            NOTIFY fontsApplicationChanged FINAL)
    /* fonts/comboBox/delegate/highlighted */ Q_PROPERTY(
        QFont fontsComboBoxDelegateHighlighted READ
            fontsComboBoxDelegateHighlighted WRITE
                setFontsComboBoxDelegateHighlighted NOTIFY
                    fontsComboBoxDelegateHighlightedChanged FINAL)
    /* fonts/dialog/titleLabel */ Q_PROPERTY(
        QFont fontsDialogTitleLabel READ fontsDialogTitleLabel WRITE
            setFontsDialogTitleLabel NOTIFY fontsDialogTitleLabelChanged FINAL)
    /* fonts/elapsedLabel */ Q_PROPERTY(
        QFont fontsElapsedLabel READ fontsElapsedLabel WRITE
            setFontsElapsedLabel NOTIFY fontsElapsedLabelChanged FINAL)
    /* fonts/mainWindow/footerLabel */ Q_PROPERTY(
        QFont fontsMainWindowFooterLabel READ fontsMainWindowFooterLabel WRITE
            setFontsMainWindowFooterLabel NOTIFY
                fontsMainWindowFooterLabelChanged FINAL)
    /* fonts/nowPlayingLabel */ Q_PROPERTY(
        QFont fontsNowPlayingLabel READ fontsNowPlayingLabel WRITE
            setFontsNowPlayingLabel NOTIFY fontsNowPlayingLabelChanged FINAL)
    /* fonts/stationImage/stationLoadingIndicator */ Q_PROPERTY(
        QFont fontsStationImageStationLoadingIndicator READ
            fontsStationImageStationLoadingIndicator WRITE
                setFontsStationImageStationLoadingIndicator NOTIFY
                    fontsStationImageStationLoadingIndicatorChanged FINAL)
    // ================================

    // palette
    /* palette/accent */ Q_PROPERTY(
        QColor paletteAccent READ paletteAccent WRITE setPaletteAccent NOTIFY
            paletteAccentChanged FINAL)
    /* palette/accent/active */ Q_PROPERTY(
        QColor paletteAccentActive READ paletteAccentActive WRITE
            setPaletteAccentActive NOTIFY paletteAccentActiveChanged FINAL)
    /* palette/accent/darker */ Q_PROPERTY(
        QColor paletteAccentDarker READ paletteAccentDarker WRITE
            setPaletteAccentDarker NOTIFY paletteAccentDarkerChanged FINAL)
    /* palette/accent/lighter */ Q_PROPERTY(
        QColor paletteAccentLighter READ paletteAccentLighter WRITE
            setPaletteAccentLighter NOTIFY paletteAccentLighterChanged FINAL)
    /* palette/activeFocusBackground */ Q_PROPERTY(
        QColor paletteActiveFocusBackground READ paletteActiveFocusBackground
            WRITE setPaletteActiveFocusBackground NOTIFY
                paletteActiveFocusBackgroundChanged FINAL)
    /* palette/background */ Q_PROPERTY(
        QColor paletteBackground READ paletteBackground WRITE
            setPaletteBackground NOTIFY paletteBackgroundChanged FINAL)
    /* palette/dialog/modal */ Q_PROPERTY(
        QColor paletteDialogModal READ paletteDialogModal WRITE
            setPaletteDialogModal NOTIFY paletteDialogModalChanged FINAL)
    /* palette/dialog/modeless */ Q_PROPERTY(
        QColor paletteDialogModeless READ paletteDialogModeless WRITE
            setPaletteDialogModeless NOTIFY paletteDialogModelessChanged FINAL)
    /* palette/menu/modal */ Q_PROPERTY(
        QColor paletteMenuModal READ paletteMenuModal WRITE setPaletteMenuModal
            NOTIFY paletteMenuModalChanged FINAL)
    /* palette/menu/modeless */ Q_PROPERTY(
        QColor paletteMenuModeless READ paletteMenuModeless WRITE
            setPaletteMenuModeless NOTIFY paletteMenuModelessChanged FINAL)
    /* palette/scrollIndicator/color */ Q_PROPERTY(
        QColor paletteScrollIndicatorColor READ paletteScrollIndicatorColor
            WRITE setPaletteScrollIndicatorColor NOTIFY
                paletteScrollIndicatorColorChanged FINAL)
    /* palette/stationImage/disabled */ Q_PROPERTY(
        QColor paletteStationImageDisabled READ paletteStationImageDisabled
            WRITE setPaletteStationImageDisabled NOTIFY
                paletteStationImageDisabledChanged FINAL)
    /* palette/stationImage/stationLoadingIndicator/background */ Q_PROPERTY(
        QColor paletteStationImageStationLoadingIndicatorBackground READ
            paletteStationImageStationLoadingIndicatorBackground WRITE
                setPaletteStationImageStationLoadingIndicatorBackground NOTIFY
                    paletteStationImageStationLoadingIndicatorBackgroundChanged
                        FINAL)
    /* palette/stationImage/stationLoadingIndicator/text */ Q_PROPERTY(
        QColor paletteStationImageStationLoadingIndicatorText READ
            paletteStationImageStationLoadingIndicatorText WRITE
                setPaletteStationImageStationLoadingIndicatorText NOTIFY
                    paletteStationImageStationLoadingIndicatorTextChanged FINAL)
    /* palette/text */ Q_PROPERTY(
        QColor paletteText READ paletteText WRITE setPaletteText NOTIFY
            paletteTextChanged FINAL)
    /* palette/textLink */ Q_PROPERTY(
        QColor paletteTextLink READ paletteTextLink WRITE setPaletteTextLink
            NOTIFY paletteTextLinkChanged FINAL)
    /* palette/textLink/darker */ Q_PROPERTY(
        QColor paletteTextLinkDarker READ paletteTextLinkDarker WRITE
            setPaletteTextLinkDarker NOTIFY paletteTextLinkDarkerChanged FINAL)
    /* palette/text/active */ Q_PROPERTY(
        QColor paletteTextActive READ paletteTextActive WRITE
            setPaletteTextActive NOTIFY paletteTextActiveChanged FINAL)
    /* palette/text/darker */ Q_PROPERTY(
        QColor paletteTextDarker READ paletteTextDarker WRITE
            setPaletteTextDarker NOTIFY paletteTextDarkerChanged FINAL)
    /* palette/text/lighter */ Q_PROPERTY(
        QColor paletteTextLighter READ paletteTextLighter WRITE
            setPaletteTextLighter NOTIFY paletteTextLighterChanged FINAL)

private:
    static const QHash<QString, QVariant> m_defaults;

    StyleSettings();

    QVariant getDefault(const QString &path) const override;

public:
    static StyleSettings *instance();
    static StyleSettings *create(QQmlEngine *, QJSEngine *);

    int borderWidth() const;
    void setBorderWidth(const int &);

    int controlsComboBoxIndicatorPadding() const;
    void setControlsComboBoxIndicatorPadding(const int &);
    int controlsIconButtonPadding() const;
    void setControlsIconButtonPadding(const int &);
    int controlsItemDelegateIconSize() const;
    void setControlsItemDelegateIconSize(const int &);
    int controlsMargins() const;
    void setControlsMargins(const int &);
    int controlsMenuBarItemIconSize() const;
    void setControlsMenuBarItemIconSize(const int &);
    int controlsMenuItemIconSize() const;
    void setControlsMenuItemIconSize(const int &);
    int controlsMenuOverlap() const;
    void setControlsMenuOverlap(const int &);
    int controlsPadding() const;
    void setControlsPadding(const int &);
    qreal controlsScrollIndicatorOpacityActive() const;
    void setControlsScrollIndicatorOpacityActive(const qreal &);
    qreal controlsScrollIndicatorOpacityInactive() const;
    void setControlsScrollIndicatorOpacityInactive(const qreal &);
    int controlsScrollIndicatorPadding() const;
    void setControlsScrollIndicatorPadding(const int &);
    int controlsScrollIndicatorPauseDuration() const;
    void setControlsScrollIndicatorPauseDuration(const int &);
    int controlsScrollIndicatorSize() const;
    void setControlsScrollIndicatorSize(const int &);
    int controlsScrollIndicatorSwitchToInactiveDuration() const;
    void setControlsScrollIndicatorSwitchToInactiveDuration(const int &);
    int controlsSeparatorSize() const;
    void setControlsSeparatorSize(const int &);
    int controlsSliderHandleHeight() const;
    void setControlsSliderHandleHeight(const int &);
    int controlsSliderHandleWidth() const;
    void setControlsSliderHandleWidth(const int &);
    int controlsSliderImplicitHeight() const;
    void setControlsSliderImplicitHeight(const int &);
    int controlsSliderImplicitWidth() const;
    void setControlsSliderImplicitWidth(const int &);
    int controlsSpacing() const;
    void setControlsSpacing(const int &);
    qreal controlsStationImageOpacityDisabled() const;
    void setControlsStationImageOpacityDisabled(const qreal &);
    int controlsStationImagePadding() const;
    void setControlsStationImagePadding(const int &);
    int controlsStationImageSize() const;
    void setControlsStationImageSize(const int &);
    qreal controlsStationImageStationLoadingIndicatorBackgroundOpacity() const;
    void setControlsStationImageStationLoadingIndicatorBackgroundOpacity(
        const qreal &);
    bool controlsStationImageStationLoadingIndicatorBounceBack() const;
    void setControlsStationImageStationLoadingIndicatorBounceBack(const bool &);
    QStringList controlsStationImageStationLoadingIndicatorFrames() const;
    void setControlsStationImageStationLoadingIndicatorFrames(
        const QStringList &);
    int controlsStationImageStationLoadingIndicatorInterval() const;
    void setControlsStationImageStationLoadingIndicatorInterval(const int &);
    int controlsTopLayoutControlLayoutHeight() const;
    void setControlsTopLayoutControlLayoutHeight(const int &);
    int controlsVolumeSliderVerticalPadding() const;
    void setControlsVolumeSliderVerticalPadding(const int &);

    int dialogsAboutDialogMaximumWidth() const;
    void setDialogsAboutDialogMaximumWidth(const int &);
    int dialogsMessageDialogMaximumWidth() const;
    void setDialogsMessageDialogMaximumWidth(const int &);
    int dialogsOpenLocationDialogMaximumWidth() const;
    void setDialogsOpenLocationDialogMaximumWidth(const int &);

    QFont fontsApplication() const;
    void setFontsApplication(const QFont &);
    QFont fontsComboBoxDelegateHighlighted() const;
    void setFontsComboBoxDelegateHighlighted(const QFont &);
    QFont fontsDialogTitleLabel() const;
    void setFontsDialogTitleLabel(const QFont &);
    QFont fontsElapsedLabel() const;
    void setFontsElapsedLabel(const QFont &);
    QFont fontsMainWindowFooterLabel() const;
    void setFontsMainWindowFooterLabel(const QFont &);
    QFont fontsNowPlayingLabel() const;
    void setFontsNowPlayingLabel(const QFont &);
    QFont fontsStationImageStationLoadingIndicator() const;
    void setFontsStationImageStationLoadingIndicator(const QFont &);

    QColor paletteAccent() const;
    void setPaletteAccent(const QColor &);
    QColor paletteAccentActive() const;
    void setPaletteAccentActive(const QColor &);
    QColor paletteAccentDarker() const;
    void setPaletteAccentDarker(const QColor &);
    QColor paletteAccentLighter() const;
    void setPaletteAccentLighter(const QColor &);
    QColor paletteActiveFocusBackground() const;
    void setPaletteActiveFocusBackground(const QColor &);
    QColor paletteBackground() const;
    void setPaletteBackground(const QColor &);
    QColor paletteDialogModal() const;
    void setPaletteDialogModal(const QColor &);
    QColor paletteDialogModeless() const;
    void setPaletteDialogModeless(const QColor &);
    QColor paletteMenuModal() const;
    void setPaletteMenuModal(const QColor &);
    QColor paletteMenuModeless() const;
    void setPaletteMenuModeless(const QColor &);
    QColor paletteScrollIndicatorColor() const;
    void setPaletteScrollIndicatorColor(const QColor &);
    QColor paletteStationImageDisabled() const;
    void setPaletteStationImageDisabled(const QColor &);
    QColor paletteStationImageStationLoadingIndicatorBackground() const;
    void
        setPaletteStationImageStationLoadingIndicatorBackground(const QColor &);
    QColor paletteStationImageStationLoadingIndicatorText() const;
    void setPaletteStationImageStationLoadingIndicatorText(const QColor &);
    QColor paletteText() const;
    void setPaletteText(const QColor &);
    QColor paletteTextLink() const;
    void setPaletteTextLink(const QColor &);
    QColor paletteTextLinkDarker() const;
    void setPaletteTextLinkDarker(const QColor &);
    QColor paletteTextActive() const;
    void setPaletteTextActive(const QColor &);
    QColor paletteTextDarker() const;
    void setPaletteTextDarker(const QColor &);
    QColor paletteTextLighter() const;
    void setPaletteTextLighter(const QColor &);

signals:
    void borderWidthChanged();

    void controlsComboBoxIndicatorPaddingChanged();
    void controlsIconButtonPaddingChanged();
    void controlsItemDelegateIconSizeChanged();
    void controlsMarginsChanged();
    void controlsMenuBarItemIconSizeChanged();
    void controlsMenuItemIconSizeChanged();
    void controlsMenuOverlapChanged();
    void controlsPaddingChanged();
    void controlsScrollIndicatorOpacityActiveChanged();
    void controlsScrollIndicatorOpacityInactiveChanged();
    void controlsScrollIndicatorPaddingChanged();
    void controlsScrollIndicatorPauseDurationChanged();
    void controlsScrollIndicatorSizeChanged();
    void controlsScrollIndicatorSwitchToInactiveDurationChanged();
    void controlsSeparatorSizeChanged();
    void controlsSliderHandleHeightChanged();
    void controlsSliderHandleWidthChanged();
    void controlsSliderImplicitHeightChanged();
    void controlsSliderImplicitWidthChanged();
    void controlsSpacingChanged();
    void controlsStationImageOpacityDisabledChanged();
    void controlsStationImagePaddingChanged();
    void controlsStationImageSizeChanged();
    void controlsStationImageStationLoadingIndicatorBackgroundOpacityChanged();
    void controlsStationImageStationLoadingIndicatorBounceBackChanged();
    void controlsStationImageStationLoadingIndicatorFramesChanged();
    void controlsStationImageStationLoadingIndicatorIntervalChanged();
    void controlsTopLayoutControlLayoutHeightChanged();
    void controlsVolumeSliderVerticalPaddingChanged();

    void dialogsAboutDialogMaximumWidthChanged();
    void dialogsMessageDialogMaximumWidthChanged();
    void dialogsOpenLocationDialogMaximumWidthChanged();

    void fontsApplicationChanged();
    void fontsComboBoxDelegateHighlightedChanged();
    void fontsDialogTitleLabelChanged();
    void fontsElapsedLabelChanged();
    void fontsMainWindowFooterLabelChanged();
    void fontsNowPlayingLabelChanged();
    void fontsStationImageStationLoadingIndicatorChanged();

    void paletteAccentChanged();
    void paletteAccentActiveChanged();
    void paletteAccentDarkerChanged();
    void paletteAccentLighterChanged();
    void paletteActiveFocusBackgroundChanged();
    void paletteBackgroundChanged();
    void paletteDialogModalChanged();
    void paletteDialogModelessChanged();
    void paletteMenuModalChanged();
    void paletteMenuModelessChanged();
    void paletteScrollIndicatorColorChanged();
    void paletteStationImageDisabledChanged();
    void paletteStationImageStationLoadingIndicatorBackgroundChanged();
    void paletteStationImageStationLoadingIndicatorTextChanged();
    void paletteTextChanged();
    void paletteTextLinkChanged();
    void paletteTextLinkDarkerChanged();
    void paletteTextActiveChanged();
    void paletteTextDarkerChanged();
    void paletteTextLighterChanged();
};
