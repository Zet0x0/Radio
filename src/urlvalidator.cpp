#include "urlvalidator.h"

QValidator::State UrlValidator::validate(QString &input, int &) const
{
    if (input.startsWith(' '))
    {
        return QValidator::Invalid;
    }

    if (input.isEmpty())
    {
        return QValidator::Intermediate;
    }

    QUrl url(input);

    return (url.scheme().isEmpty() || !url.isValid()) ? QValidator::Intermediate
                                                      : QValidator::Acceptable;
}

void UrlValidator::fixup(QString &input) const
{
    while (input.startsWith(' '))
    {
        input.chop(1);
    }

    input = QUrl(input).toString();
}
