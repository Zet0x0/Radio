#include "stylesettings.h"

/*

           ) (   (      (    (   (          (   (              (   (
  *   ) ( /( )\ ))\ )   )\ ) )\ ))\ )       )\ ))\ )     (     )\ ))\ )
` )  /( )\()|()/(()/(  (()/((()/(()/( (    (()/(()/(     )\   (()/(()/(
 ( )(_)|(_)\ /(_))(_))  /(_))/(_))(_)))\    /(_))(_)) ((((_)(  /(_))(_))
(_(_()) _((_|_))(_))   (_))_(_))(_)) ((_)  (_))(_))    )\ _ )\(_))(_))
|_   _|| || |_ _/ __|  | |_ |_ _| |  | __| |_ _/ __|   (_)_\(_) __/ __|
  | |  | __ || |\__ \  | __| | || |__| _|   | |\__ \    / _ \ \__ \__ \
  |_|  |_||_|___|___/  |_|  |___|____|___| |___|___/   /_/ \_\|___/___/, too

 */

const QHash<QString, QVariant> StyleSettings::m_defaults = {
    { "border/width", 1 },
    { "controls/comboBox/indicator/padding", 3 },
    { "controls/iconButton/padding", 3 },
    { "controls/itemDelegate/iconSize", 20 },
    { "controls/margins", 5 },
    { "controls/menuBarItem/iconSize", 20 },
    { "controls/menuItem/iconSize", 20 },
    { "controls/menu/overlap", 1 },
    { "controls/padding", 5 },
    { "controls/scrollIndicator/opacity/active", 0.5 },
    { "controls/scrollIndicator/opacity/inactive", 0.0 },
    { "controls/scrollIndicator/padding", 3 },
    { "controls/scrollIndicator/pauseDuration", 450 },
    { "controls/scrollIndicator/size", 3 },
    { "controls/scrollIndicator/switchToInactiveDuration", 150 },
    { "controls/separator/size", 1 },
    { "controls/slider/handle/height", 26 },
    { "controls/slider/handle/width", 10 },
    { "controls/slider/implicitHeight", 4 },
    { "controls/slider/implicitWidth", 200 },
    { "controls/spacing", 5 },
    { "controls/stationImage/opacity/disabled", 0.5 },
    { "controls/stationImage/padding", 5 },
    { "controls/stationImage/size", 96 },
    { "controls/stationImage/stationLoadingIndicator/background/opacity",
     0.75 },
    { "controls/stationImage/stationLoadingIndicator/bounceBack", false },
    { "controls/stationImage/stationLoadingIndicator/frames",
     QStringList{ "010010",
                   "001100",
                   "100101",
                   "111010",
                   "111101",
                   "010111",
                   "101011",
                   "111000",
                   "110011",
                   "110101" } },
    { "controls/stationImage/stationLoadingIndicator/interval", 80 },
    { "controls/topLayout/controlLayout/height", 32 },
    { "controls/volumeSlider/verticalPadding", 3 },
    { "dialogs/aboutDialog/maximumWidth", 512 },
    { "dialogs/messageDialog/maximumWidth", 512 },
    { "dialogs/openLocationDialog/maximumWidth", 512 },
    { "fonts/application", QFont("Segoe UI Variable", 10, QFont::DemiBold) },
    { "fonts/comboBox/delegate/highlighted",
     QFont("Segoe UI Variable", -1, QFont::Bold) },
    { "fonts/dialog/titleLabel", QFont("Segoe UI Variable", -1, QFont::Bold) },
    { "fonts/elapsedLabel", QFont("Consolas") },
    { "fonts/mainWindow/footerLabel", QFont("Consolas") },
    { "fonts/nowPlayingLabel", QFont("Segoe UI Variable", 12, QFont::Bold) },
    { "fonts/stationImage/stationLoadingIndicator",
     QFont("Consolas", 12, QFont::Bold) },
    { "palette/accent", QColor(170, 0, 255) },
    { "palette/accent/active", QColor(255, 255, 255) },
    { "palette/accent/darker", QColor(170, 0, 255).darker() },
    { "palette/accent/lighter", QColor(170, 0, 255).lighter() },
    { "palette/activeFocusBackground", QColor(85, 0, 127) },
    { "palette/background", QColor(0, 0, 0) },
    { "palette/dialog/modal", QColor::fromRgbF(0., 0., 0., 0.5) },
    { "palette/dialog/modeless", QColor::fromRgbF(0., 0., 0., 0.5) },
    { "palette/menu/modal", QColor::fromRgbF(0., 0., 0., 0.5) },
    { "palette/menu/modeless", QColor::fromRgbF(0., 0., 0., 0.5) },
    { "palette/scrollIndicator/color", QColor(255, 255, 255) },
    { "palette/stationImage/disabled", QColor(0, 0, 0) },
    { "palette/stationImage/stationLoadingIndicator/background",
     QColor(0, 0, 0) },
    { "palette/stationImage/stationLoadingIndicator/text",
     QColor(255, 255, 255) },
    { "palette/text", QColor(170, 0, 255) },
    { "palette/textLink", QColor(212, 127, 255) },
    { "palette/textLink/darker", QColor(212, 127, 255).darker() },
    { "palette/text/active", QColor(255, 255, 255) },
    { "palette/text/darker", QColor(170, 0, 255).darker() },
    { "palette/text/lighter", QColor(170, 0, 255).lighter() }
};

StyleSettings::StyleSettings()
    : SettingsBase("styleSettings.ini")
{
}

QVariant StyleSettings::getDefault(const QString &path) const
{
    return m_defaults.value(path);
}

StyleSettings *StyleSettings::instance()
{
    static StyleSettings *instance = new StyleSettings;

    return instance;
}

StyleSettings *StyleSettings::create(QQmlEngine *, QJSEngine *)
{
    return instance();
}

int StyleSettings::borderWidth() const
{
    return readVariant<int>("border/width");
}

void StyleSettings::setBorderWidth(const int &newValue)
{
    writeVariant<int>("border/width", newValue);

    emit borderWidthChanged();
}

int StyleSettings::controlsComboBoxIndicatorPadding() const
{
    return readVariant<int>("controls/comboBox/indicator/padding");
}

void StyleSettings::setControlsComboBoxIndicatorPadding(const int &newValue)
{
    writeVariant<int>("controls/comboBox/indicator/padding", newValue);

    emit controlsComboBoxIndicatorPaddingChanged();
}

int StyleSettings::controlsIconButtonPadding() const
{
    return readVariant<int>("controls/iconButton/padding");
}

void StyleSettings::setControlsIconButtonPadding(const int &newValue)
{
    writeVariant<int>("controls/iconButton/padding", newValue);

    emit controlsIconButtonPaddingChanged();
}

int StyleSettings::controlsItemDelegateIconSize() const
{
    return readVariant<int>("controls/itemDelegate/iconSize");
}

void StyleSettings::setControlsItemDelegateIconSize(const int &newValue)
{
    writeVariant<int>("controls/itemDelegate/iconSize", newValue);

    emit controlsItemDelegateIconSizeChanged();
}

int StyleSettings::controlsMargins() const
{
    return readVariant<int>("controls/margins");
}

void StyleSettings::setControlsMargins(const int &newValue)
{
    writeVariant<int>("controls/margins", newValue);

    emit controlsMarginsChanged();
}

int StyleSettings::controlsMenuBarItemIconSize() const
{
    return readVariant<int>("controls/menuBarItem/iconSize");
}

void StyleSettings::setControlsMenuBarItemIconSize(const int &newValue)
{
    writeVariant<int>("controls/menuBarItem/iconSize", newValue);

    emit controlsMenuBarItemIconSizeChanged();
}

int StyleSettings::controlsMenuItemIconSize() const
{
    return readVariant<int>("controls/menuItem/iconSize");
}

void StyleSettings::setControlsMenuItemIconSize(const int &newValue)
{
    writeVariant<int>("controls/menuItem/iconSize", newValue);

    emit controlsMenuItemIconSizeChanged();
}

int StyleSettings::controlsMenuOverlap() const
{
    return readVariant<int>("controls/menu/overlap");
}

void StyleSettings::setControlsMenuOverlap(const int &newValue)
{
    writeVariant<int>("controls/menu/overlap", newValue);

    emit controlsMenuOverlapChanged();
}

int StyleSettings::controlsPadding() const
{
    return readVariant<int>("controls/padding");
}

void StyleSettings::setControlsPadding(const int &newValue)
{
    writeVariant<int>("controls/padding", newValue);

    emit controlsPaddingChanged();
}

qreal StyleSettings::controlsScrollIndicatorOpacityActive() const
{
    return readVariant<qreal>("controls/scrollIndicator/opacity/active");
}

void StyleSettings::setControlsScrollIndicatorOpacityActive(
    const qreal &newValue)
{
    writeVariant<qreal>("controls/scrollIndicator/opacity/active", newValue);

    emit controlsScrollIndicatorOpacityActiveChanged();
}

qreal StyleSettings::controlsScrollIndicatorOpacityInactive() const
{
    return readVariant<qreal>("controls/scrollIndicator/opacity/inactive");
}

void StyleSettings::setControlsScrollIndicatorOpacityInactive(
    const qreal &newValue)
{
    writeVariant<qreal>("controls/scrollIndicator/opacity/inactive", newValue);

    emit controlsScrollIndicatorOpacityInactiveChanged();
}

int StyleSettings::controlsScrollIndicatorPadding() const
{
    return readVariant<int>("controls/scrollIndicator/padding");
}

void StyleSettings::setControlsScrollIndicatorPadding(const int &newValue)
{
    writeVariant<int>("controls/scrollIndicator/padding", newValue);

    emit controlsScrollIndicatorPaddingChanged();
}

int StyleSettings::controlsScrollIndicatorPauseDuration() const
{
    return readVariant<int>("controls/scrollIndicator/pauseDuration");
}

void StyleSettings::setControlsScrollIndicatorPauseDuration(const int &newValue)
{
    writeVariant<int>("controls/scrollIndicator/pauseDuration", newValue);

    emit controlsScrollIndicatorPauseDurationChanged();
}

int StyleSettings::controlsScrollIndicatorSize() const
{
    return readVariant<int>("controls/scrollIndicator/size");
}

void StyleSettings::setControlsScrollIndicatorSize(const int &newValue)
{
    writeVariant<int>("controls/scrollIndicator/size", newValue);

    emit controlsScrollIndicatorSizeChanged();
}

int StyleSettings::controlsScrollIndicatorSwitchToInactiveDuration() const
{
    return readVariant<int>(
        "controls/scrollIndicator/switchToInactiveDuration");
}

void StyleSettings::setControlsScrollIndicatorSwitchToInactiveDuration(
    const int &newValue)
{
    writeVariant<int>("controls/scrollIndicator/switchToInactiveDuration",
                      newValue);

    emit controlsScrollIndicatorSwitchToInactiveDurationChanged();
}

int StyleSettings::controlsSeparatorSize() const
{
    return readVariant<int>("controls/separator/size");
}

void StyleSettings::setControlsSeparatorSize(const int &newValue)
{
    writeVariant<int>("controls/separator/size", newValue);

    emit controlsSeparatorSizeChanged();
}

int StyleSettings::controlsSliderHandleHeight() const
{
    return readVariant<int>("controls/slider/handle/height");
}

void StyleSettings::setControlsSliderHandleHeight(const int &newValue)
{
    writeVariant<int>("controls/slider/handle/height", newValue);

    emit controlsSliderHandleHeightChanged();
}

int StyleSettings::controlsSliderHandleWidth() const
{
    return readVariant<int>("controls/slider/handle/width");
}

void StyleSettings::setControlsSliderHandleWidth(const int &newValue)
{
    writeVariant<int>("controls/slider/handle/width", newValue);

    emit controlsSliderHandleWidthChanged();
}

int StyleSettings::controlsSliderImplicitHeight() const
{
    return readVariant<int>("controls/slider/implicitHeight");
}

void StyleSettings::setControlsSliderImplicitHeight(const int &newValue)
{
    writeVariant<int>("controls/slider/implicitHeight", newValue);

    emit controlsSliderImplicitHeightChanged();
}

int StyleSettings::controlsSliderImplicitWidth() const
{
    return readVariant<int>("controls/slider/implicitWidth");
}

void StyleSettings::setControlsSliderImplicitWidth(const int &newValue)
{
    writeVariant<int>("controls/slider/implicitWidth", newValue);

    emit controlsSliderImplicitWidthChanged();
}

int StyleSettings::controlsSpacing() const
{
    return readVariant<int>("controls/spacing");
}

void StyleSettings::setControlsSpacing(const int &newValue)
{
    writeVariant<int>("controls/spacing", newValue);

    emit controlsSpacingChanged();
}

qreal StyleSettings::controlsStationImageOpacityDisabled() const
{
    return readVariant<qreal>("controls/stationImage/opacity/disabled");
}

void
    StyleSettings::setControlsStationImageOpacityDisabled(const qreal &newValue)
{
    writeVariant<qreal>("controls/stationImage/opacity/disabled", newValue);

    emit controlsStationImageOpacityDisabledChanged();
}

int StyleSettings::controlsStationImagePadding() const
{
    return readVariant<int>("controls/stationImage/padding");
}

void StyleSettings::setControlsStationImagePadding(const int &newValue)
{
    writeVariant<int>("controls/stationImage/padding", newValue);

    emit controlsStationImagePaddingChanged();
}

int StyleSettings::controlsStationImageSize() const
{
    return readVariant<int>("controls/stationImage/size");
}

void StyleSettings::setControlsStationImageSize(const int &newValue)
{
    writeVariant<int>("controls/stationImage/size", newValue);

    emit controlsStationImageSizeChanged();
}

qreal StyleSettings::
    controlsStationImageStationLoadingIndicatorBackgroundOpacity() const
{
    return readVariant<qreal>(
        "controls/stationImage/stationLoadingIndicator/background/opacity");
}

void StyleSettings::
    setControlsStationImageStationLoadingIndicatorBackgroundOpacity(
        const qreal &newValue)
{
    writeVariant<qreal>(
        "controls/stationImage/stationLoadingIndicator/background/opacity",
        newValue);

    emit controlsStationImageStationLoadingIndicatorBackgroundOpacityChanged();
}

bool
    StyleSettings::controlsStationImageStationLoadingIndicatorBounceBack() const
{
    return readVariant<bool>(
        "controls/stationImage/stationLoadingIndicator/bounceBack");
}

void StyleSettings::setControlsStationImageStationLoadingIndicatorBounceBack(
    const bool &newValue)
{
    writeVariant<bool>(
        "controls/stationImage/stationLoadingIndicator/bounceBack",
        newValue);

    emit controlsStationImageStationLoadingIndicatorBounceBackChanged();
}

QStringList
    StyleSettings::controlsStationImageStationLoadingIndicatorFrames() const
{
    return readVariant<QStringList>(
        "controls/stationImage/stationLoadingIndicator/frames");
}

void StyleSettings::setControlsStationImageStationLoadingIndicatorFrames(
    const QStringList &newValue)
{
    writeVariant<QStringList>(
        "controls/stationImage/stationLoadingIndicator/frames",
        newValue);

    emit controlsStationImageStationLoadingIndicatorFramesChanged();
}

int StyleSettings::controlsStationImageStationLoadingIndicatorInterval() const
{
    return readVariant<int>(
        "controls/stationImage/stationLoadingIndicator/interval");
}

void StyleSettings::setControlsStationImageStationLoadingIndicatorInterval(
    const int &newValue)
{
    writeVariant<int>("controls/stationImage/stationLoadingIndicator/interval",
                      newValue);

    emit controlsStationImageStationLoadingIndicatorIntervalChanged();
}

int StyleSettings::controlsTopLayoutControlLayoutHeight() const
{
    return readVariant<int>("controls/topLayout/controlLayout/height");
}

void StyleSettings::setControlsTopLayoutControlLayoutHeight(const int &newValue)
{
    writeVariant<int>("controls/topLayout/controlLayout/height", newValue);

    emit controlsTopLayoutControlLayoutHeightChanged();
}

int StyleSettings::controlsVolumeSliderVerticalPadding() const
{
    return readVariant<int>("controls/volumeSlider/verticalPadding");
}

void StyleSettings::setControlsVolumeSliderVerticalPadding(const int &newValue)
{
    writeVariant<int>("controls/volumeSlider/verticalPadding", newValue);

    emit controlsVolumeSliderVerticalPaddingChanged();
}

int StyleSettings::dialogsAboutDialogMaximumWidth() const
{
    return readVariant<int>("dialogs/aboutDialog/maximumWidth");
}

void StyleSettings::setDialogsAboutDialogMaximumWidth(const int &newValue)
{
    writeVariant<int>("dialogs/aboutDialog/maximumWidth", newValue);

    emit dialogsAboutDialogMaximumWidthChanged();
}

int StyleSettings::dialogsMessageDialogMaximumWidth() const
{
    return readVariant<int>("dialogs/messageDialog/maximumWidth");
}

void StyleSettings::setDialogsMessageDialogMaximumWidth(const int &newValue)
{
    writeVariant<int>("dialogs/messageDialog/maximumWidth", newValue);

    emit dialogsMessageDialogMaximumWidthChanged();
}

int StyleSettings::dialogsOpenLocationDialogMaximumWidth() const
{
    return readVariant<int>("dialogs/openLocationDialog/maximumWidth");
}

void
    StyleSettings::setDialogsOpenLocationDialogMaximumWidth(const int &newValue)
{
    writeVariant<int>("dialogs/openLocationDialog/maximumWidth", newValue);

    emit dialogsMessageDialogMaximumWidthChanged();
}

QFont StyleSettings::fontsApplication() const
{
    return readVariant<QFont>("fonts/application");
}

void StyleSettings::setFontsApplication(const QFont &newValue)
{
    writeVariant<QFont>("fonts/application", newValue);

    emit fontsApplicationChanged();
}

QFont StyleSettings::fontsComboBoxDelegateHighlighted() const
{
    return readVariant<QFont>("fonts/comboBox/delegate/highlighted");
}

void StyleSettings::setFontsComboBoxDelegateHighlighted(const QFont &newValue)
{
    writeVariant<QFont>("fonts/comboBox/delegate/highlighted", newValue);

    emit fontsComboBoxDelegateHighlightedChanged();
}

QFont StyleSettings::fontsDialogTitleLabel() const
{
    return readVariant<QFont>("fonts/dialog/titleLabel");
}

void StyleSettings::setFontsDialogTitleLabel(const QFont &newValue)
{
    writeVariant<QFont>("fonts/dialog/titleLabel", newValue);

    emit fontsDialogTitleLabelChanged();
}

QFont StyleSettings::fontsElapsedLabel() const
{
    return readVariant<QFont>("fonts/elapsedLabel");
}

void StyleSettings::setFontsElapsedLabel(const QFont &newValue)
{
    writeVariant<QFont>("fonts/elapsedLabel", newValue);

    emit fontsElapsedLabelChanged();
}

QFont StyleSettings::fontsMainWindowFooterLabel() const
{
    return readVariant<QFont>("fonts/mainWindow/footerLabel");
}

void StyleSettings::setFontsMainWindowFooterLabel(const QFont &newValue)
{
    writeVariant<QFont>("fonts/mainWindow/footerLabel", newValue);

    emit fontsMainWindowFooterLabelChanged();
}

QFont StyleSettings::fontsNowPlayingLabel() const
{
    return readVariant<QFont>("fonts/nowPlayingLabel");
}

void StyleSettings::setFontsNowPlayingLabel(const QFont &newValue)
{
    writeVariant<QFont>("fonts/nowPlayingLabel", newValue);

    emit fontsNowPlayingLabelChanged();
}

QFont StyleSettings::fontsStationImageStationLoadingIndicator() const
{
    return readVariant<QFont>("fonts/stationImage/stationLoadingIndicator");
}

void StyleSettings::setFontsStationImageStationLoadingIndicator(
    const QFont &newValue)
{
    writeVariant<QFont>("fonts/stationImage/stationLoadingIndicator", newValue);

    emit fontsStationImageStationLoadingIndicatorChanged();
}

QColor StyleSettings::paletteAccent() const
{
    return readVariant<QColor>("palette/accent");
}

void StyleSettings::setPaletteAccent(const QColor &newValue)
{
    writeVariant<QColor>("palette/accent", newValue);

    emit paletteAccentChanged();
}

QColor StyleSettings::paletteAccentActive() const
{
    return readVariant<QColor>("palette/accent/active");
}

void StyleSettings::setPaletteAccentActive(const QColor &newValue)
{
    writeVariant<QColor>("palette/accent/active", newValue);

    emit paletteAccentActiveChanged();
}

QColor StyleSettings::paletteAccentDarker() const
{
    return readVariant<QColor>("palette/accent/darker");
}

void StyleSettings::setPaletteAccentDarker(const QColor &newValue)
{
    writeVariant<QColor>("palette/accent/darker", newValue);

    emit paletteAccentDarkerChanged();
}

QColor StyleSettings::paletteAccentLighter() const
{
    return readVariant<QColor>("palette/accent/lighter");
}

void StyleSettings::setPaletteAccentLighter(const QColor &newValue)
{
    writeVariant<QColor>("palette/accent/lighter", newValue);

    emit paletteAccentLighterChanged();
}

QColor StyleSettings::paletteActiveFocusBackground() const
{
    return readVariant<QColor>("palette/activeFocusBackground");
}

void StyleSettings::setPaletteActiveFocusBackground(const QColor &newValue)
{
    writeVariant<QColor>("palette/activeFocusBackground", newValue);

    emit paletteActiveFocusBackgroundChanged();
}

QColor StyleSettings::paletteBackground() const
{
    return readVariant<QColor>("palette/background");
}

void StyleSettings::setPaletteBackground(const QColor &newValue)
{
    writeVariant<QColor>("palette/background", newValue);

    emit paletteBackgroundChanged();
}

QColor StyleSettings::paletteDialogModal() const
{
    return readVariant<QColor>("palette/dialog/modal");
}

void StyleSettings::setPaletteDialogModal(const QColor &newValue)
{
    writeVariant<QColor>("palette/dialog/modal", newValue);

    emit paletteDialogModalChanged();
}

QColor StyleSettings::paletteDialogModeless() const
{
    return readVariant<QColor>("palette/dialog/modeless");
}

void StyleSettings::setPaletteDialogModeless(const QColor &newValue)
{
    writeVariant<QColor>("palette/dialog/modeless", newValue);

    emit paletteDialogModelessChanged();
}

QColor StyleSettings::paletteMenuModal() const
{
    return readVariant<QColor>("palette/menu/modal");
}

void StyleSettings::setPaletteMenuModal(const QColor &newValue)
{
    writeVariant<QColor>("palette/menu/modal", newValue);

    emit paletteMenuModalChanged();
}

QColor StyleSettings::paletteMenuModeless() const
{
    return readVariant<QColor>("palette/menu/modeless");
}

void StyleSettings::setPaletteMenuModeless(const QColor &newValue)
{
    writeVariant<QColor>("palette/menu/modeless", newValue);

    emit paletteMenuModelessChanged();
}

QColor StyleSettings::paletteScrollIndicatorColor() const
{
    return readVariant<QColor>("palette/scrollIndicator/color");
}

void StyleSettings::setPaletteScrollIndicatorColor(const QColor &newValue)
{
    writeVariant<QColor>("palette/scrollIndicator/color", newValue);

    emit paletteScrollIndicatorColorChanged();
}

QColor StyleSettings::paletteStationImageDisabled() const
{
    return readVariant<QColor>("palette/stationImage/disabled");
}

void StyleSettings::setPaletteStationImageDisabled(const QColor &newValue)
{
    writeVariant<QColor>("palette/stationImage/disabled", newValue);

    emit paletteStationImageDisabledChanged();
}

QColor
    StyleSettings::paletteStationImageStationLoadingIndicatorBackground() const
{
    return readVariant<QColor>(
        "palette/stationImage/stationLoadingIndicator/background");
}

void StyleSettings::setPaletteStationImageStationLoadingIndicatorBackground(
    const QColor &newValue)
{
    writeVariant<QColor>(
        "palette/stationImage/stationLoadingIndicator/background",
        newValue);

    emit paletteStationImageStationLoadingIndicatorBackgroundChanged();
}

QColor StyleSettings::paletteStationImageStationLoadingIndicatorText() const
{
    return readVariant<QColor>(
        "palette/stationImage/stationLoadingIndicator/text");
}

void StyleSettings::setPaletteStationImageStationLoadingIndicatorText(
    const QColor &newValue)
{
    writeVariant<QColor>("palette/stationImage/stationLoadingIndicator/text",
                         newValue);

    emit paletteStationImageStationLoadingIndicatorTextChanged();
}

QColor StyleSettings::paletteText() const
{
    return readVariant<QColor>("palette/text");
}

void StyleSettings::setPaletteText(const QColor &newValue)
{
    writeVariant<QColor>("palette/text", newValue);

    emit paletteTextChanged();
}

QColor StyleSettings::paletteTextLink() const
{
    return readVariant<QColor>("palette/textLink");
}

void StyleSettings::setPaletteTextLink(const QColor &newValue)
{
    writeVariant<QColor>("palette/textLink", newValue);

    emit paletteTextLinkChanged();
}

QColor StyleSettings::paletteTextLinkDarker() const
{
    return readVariant<QColor>("palette/textLink/darker");
}

void StyleSettings::setPaletteTextLinkDarker(const QColor &newValue)
{
    writeVariant<QColor>("palette/textLink/darker", newValue);

    emit paletteTextLinkDarkerChanged();
}

QColor StyleSettings::paletteTextActive() const
{
    return readVariant<QColor>("palette/text/active");
}

void StyleSettings::setPaletteTextActive(const QColor &newValue)
{
    writeVariant<QColor>("palette/text/active", newValue);

    emit paletteTextActiveChanged();
}

QColor StyleSettings::paletteTextDarker() const
{
    return readVariant<QColor>("palette/text/darker");
}

void StyleSettings::setPaletteTextDarker(const QColor &newValue)
{
    writeVariant<QColor>("palette/text/darker", newValue);

    emit paletteTextDarkerChanged();
}

QColor StyleSettings::paletteTextLighter() const
{
    return readVariant<QColor>("palette/text/lighter");
}

void StyleSettings::setPaletteTextLighter(const QColor &newValue)
{
    writeVariant<QColor>("palette/text/lighter", newValue);

    emit paletteTextLighterChanged();
}
