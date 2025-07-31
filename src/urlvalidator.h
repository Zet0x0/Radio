#pragma once

#include <QQmlEngine>
#include <QValidator>

class UrlValidator : public QValidator
{
    Q_OBJECT
    QML_ELEMENT

public:
    QValidator::State validate(QString &, int &cursorPosition) const override;

    void fixup(QString &) const override;
};
