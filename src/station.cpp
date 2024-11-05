#include "station.h"

bool operator==(const Station &a, const Station &b)
{
    return (a.title == b.title) && (a.subtitle == b.subtitle) && (a.imageUrl == b.imageUrl) &&
           (a.streamUrls == b.streamUrls);
}

size_t qHash(const Station &station)
{
    return qHash(station.streamUrls);
}

QDebug operator<<(QDebug debug, const Station &station)
{
    QDebugStateSaver debugSaver(debug);

    debug.nospace() << "{ title: " << station.title << "; "
                    << "subtitle: " << station.subtitle << "; "
                    << "imageUrl: " << station.imageUrl << "; "
                    << "streamUrls: " << station.streamUrls << " }";

    return debug;
}
