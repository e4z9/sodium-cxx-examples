#pragma once

#include <sqeditbase.h>

#include <QTextEdit>

#include <sodium/sodium.h>

class SQTextEdit : public SQEditBase<QTextEdit>
{
public:
    SQTextEdit(const QString &initialText);
    SQTextEdit(const sodium::stream<QString> &sText, const QString &initialText);
    SQTextEdit(const QString &initialText, const sodium::cell<bool> &enabled);
    SQTextEdit(const sodium::stream<QString> &sText,
               const QString &initialText,
               const sodium::cell<bool> &enabled);
};
