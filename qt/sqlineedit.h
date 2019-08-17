#pragma once

#include <QLineEdit>

#include <sodium/sodium.h>

class SQLineEdit : public QLineEdit
{
public:
    SQLineEdit(const QString &initialText);
    SQLineEdit(const sodium::stream<QString> &sText, const QString &initialText);
    SQLineEdit(const QString &initialText, const sodium::cell<bool> &enabled);
    SQLineEdit(const sodium::stream<QString> &sText,
               const QString &initialText,
               const sodium::cell<bool> &enabled);
    ~SQLineEdit();

    sodium::cell<QString> text;

private:
    std::function<void()> m_unsubscribe;
};
