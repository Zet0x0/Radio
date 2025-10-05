#pragma once

#include <QLoggingCategory>
#include <QNetworkInformation>
#include <QQmlEngine>

Q_DECLARE_LOGGING_CATEGORY(radioNetworkInformation)

class NetworkInformation : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT

    Q_PROPERTY(bool online READ online NOTIFY onlineChanged FINAL)

private:
    QNetworkInformation *m_networkInformation;
    bool m_online;

    NetworkInformation();

    void setOnline(const bool &);
    void updateOnline();

public:
    static NetworkInformation *instance();
    static NetworkInformation *create(QQmlEngine *, QJSEngine *);

    bool online() const;

signals:
    void onlineChanged();
};
