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

    const sodium::cell<QString> &text() const;

private:
    std::function<void()> _unsubscribe;
    sodium::cell<QString> _text;
};
