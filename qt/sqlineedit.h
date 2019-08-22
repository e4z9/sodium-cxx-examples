#pragma once

#include <sqeditbase.h>

#include <QLineEdit>

#include <sodium/sodium.h>

class SQLineEdit : public SQEditBase<QLineEdit>
{
public:
    SQLineEdit(const QString &initialText);
    SQLineEdit(const sodium::stream<QString> &sText, const QString &initialText);
    SQLineEdit(const QString &initialText, const sodium::cell<bool> &enabled);
    SQLineEdit(const sodium::stream<QString> &sText,
               const QString &initialText,
               const sodium::cell<bool> &enabled);
};
