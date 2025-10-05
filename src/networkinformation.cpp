#include "networkinformation.h"

Q_LOGGING_CATEGORY(radioNetworkInformation, "radio.networkInformation")

NetworkInformation::NetworkInformation()
{
    if (!QNetworkInformation::loadBackendByFeatures(
            QNetworkInformation::Feature::Reachability))
    {
        qCWarning(radioNetworkInformation)
            << "unable to load backend, defaulting online property to true";

        setOnline(true);
    }

    m_networkInformation = QNetworkInformation::instance();

    updateOnline();

    connect(m_networkInformation,
            &QNetworkInformation::reachabilityChanged,
            this,
            &NetworkInformation::updateOnline);
}

void NetworkInformation::setOnline(const bool &newOnline)
{
    if (newOnline == m_online)
    {
        return;
    }

    m_online = newOnline;

    if (m_online)
    {
        qCInfo(radioNetworkInformation) << "we're online";
    }
    else
    {
        qCWarning(radioNetworkInformation) << "we're offline";
    }

    emit onlineChanged();
}

void NetworkInformation::updateOnline()
{
    setOnline(m_networkInformation->reachability()
              == QNetworkInformation::Reachability::Online);
}

NetworkInformation *NetworkInformation::instance()
{
    static NetworkInformation *instance = new NetworkInformation;

    return instance;
}

NetworkInformation *NetworkInformation::create(QQmlEngine *, QJSEngine *)
{
    return instance();
}

bool NetworkInformation::online() const
{
    return m_online;
}
