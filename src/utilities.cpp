#include "utilities.h"
#include "player.h"
#include <QCoreApplication>
#include <QCursor>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>
#include <QSettings>
#include <vlc/libvlc_version.h>

Q_LOGGING_CATEGORY(radio_utility, "radio.utility")

Utilities *Utilities::instance()
{
    static Utilities *instance = new Utilities;

    return instance;
}

Utilities *Utilities::qmlInstance(QQmlEngine *, QJSEngine *)
{
    return instance();
}

void Utilities::executeProgram(const QString &program, const QStringList &arguments)
{
    const QString currentPath = QDir::currentPath();

    qCDebug(radio_utility) << "executing program" << program << "with arguments" << arguments
                           << "in path" << currentPath;

    if (QProcess::startDetached(program, arguments, currentPath))
    {
        return;
    }

    qCCritical(radio_utility) << "failed to execute program" << program << "with arguments"
                              << arguments << "in path" << currentPath;

    requestMessageDialog("Program Execution Error",
                         QString("Failed to execute program \"%0\" with arguments { \"%1\" }.")
                             .arg(program, arguments.join("\", \"")));
}

const QString Utilities::sanitizeString(QString string)
{
    if (string.isEmpty())
    {
        return string;
    }

    return string.replace('\r', "\\r")
        .replace('\n', "\\n")
        .replace('\t', "\\t")
        .replace('\f', "\\f");
}

const QString Utilities::libVlcVersion()
{
    return QString("%0.%1.%2.%3")
        .arg(QString::number(LIBVLC_VERSION_MAJOR), QString::number(LIBVLC_VERSION_MINOR),
             QString::number(LIBVLC_VERSION_REVISION), QString::number(LIBVLC_VERSION_EXTRA));
}

const QString Utilities::qtVersion()
{
    return qVersion();
}

void Utilities::setupAppProtocol()
{
    QSettings registrySettings("HKEY_CURRENT_USER\\Software\\Classes", QSettings::NativeFormat);

    const QString executablePath = QDir::toNativeSeparators(qApp->applicationFilePath());

    registrySettings.beginGroup("Radio");

    registrySettings.setValue("Default", "URL:radio");
    registrySettings.setValue("DefaultIcon/Default", executablePath);
    registrySettings.setValue("URL Protocol", "");
    registrySettings.setValue("shell/open/command/Default",
                              QString("\"%1\"").arg(executablePath) + " \"%1\"");

    registrySettings.endGroup();
}

void Utilities::requestMessageDialog(const QString &title, const QString &message,
                                     const QString &details)
{
    qCDebug(radio_utility).nospace() << "requesting a message dialog with title: " << title
                                     << ", message: " << message << ", details: " << details;

    emit instance() -> messageDialogRequested(title, message, details);
}

const QJsonDocument Utilities::parseJson(const QByteArray &byteArray, QString &errorString)
{
    QJsonParseError jsonParseError;
    const QJsonDocument json = QJsonDocument::fromJson(byteArray, &jsonParseError);

    if (jsonParseError.error != QJsonParseError::NoError)
    {
        errorString =
            QString("%0 (offset: %1)")
                .arg(jsonParseError.errorString(), QString::number(jsonParseError.offset));
    }

    return json;
}

const Station Utilities::stationFromJson(const QJsonObject &json)
{
    const QString title = json["title"].toString();

    Station station;

    station.title = (title.isEmpty()) ? "Untitled Station" : sanitizeString(title);
    station.streamUrls = json["streamUrls"].toVariant().toStringList();
    station.subtitle = sanitizeString(json["subtitle"].toString());
    station.imageUrl = json["imageUrl"].toString();

    return station;
}

const QPoint Utilities::getGlobalMousePosition()
{
    return QCursor::pos();
}
