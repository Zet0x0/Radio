#pragma once

#include <QLoggingCategory>
#include <QNetworkInformation>
#include <QQmlEngine>

Q_DECLARE_LOGGING_CATEGORY(radio_networkInformation)

class NetworkInformation : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(bool online MEMBER m_online NOTIFY onlineChanged FINAL)

private:
    QNetworkInformation *m_networkInformation{};
    bool m_initialized = false;
    bool m_online = false;

    NetworkInformation();

    void setOnline(const bool &);

signals:
    void onlineChanged(const bool &);

public:
    static NetworkInformation *qmlInstance(QQmlEngine *, QJSEngine *);

    Q_INVOKABLE bool hasInitialized();
};
