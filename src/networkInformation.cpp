#include "networkInformation.h"

Q_LOGGING_CATEGORY(radio_networkInformation, "radio.networkInformation")

NetworkInformation::NetworkInformation()
{
    if (!QNetworkInformation::loadDefaultBackend())
    {
        qCCritical(radio_networkInformation) << "unable to load default backend";

        return;
    }

    m_networkInformation = QNetworkInformation::instance();

    connect(m_networkInformation, &QNetworkInformation::reachabilityChanged, this,
            [this](QNetworkInformation::Reachability reachability)
            {
                setOnline(reachability == QNetworkInformation::Reachability::Online);
            });

    setOnline(m_networkInformation->reachability() == QNetworkInformation::Reachability::Online);

    qCDebug(radio_networkInformation) << "initialized with default backend";

    m_initialized = true;
}

NetworkInformation *NetworkInformation::qmlInstance(QQmlEngine *, QJSEngine *)
{
    static NetworkInformation *instance = new NetworkInformation;

    return instance;
}

void NetworkInformation::setOnline(const bool &online)
{
    if (online == m_online)
    {
        return;
    }

    m_online = online;

    qCDebug(radio_networkInformation) << "new value for online:" << online;

    emit onlineChanged(online);
}

bool NetworkInformation::hasInitialized()
{
    return m_initialized;
}
