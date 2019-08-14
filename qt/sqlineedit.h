#pragma once

#include <QLineEdit>

#include <sodium/sodium.h>

class SQLineEdit : public QLineEdit
{
public:
    SQLineEdit(const QString &initialText);
    SQLineEdit(const sodium::stream<QString> &sText, const QString &initialText);
    ~SQLineEdit();

    sodium::cell<QString> text;

private:
    std::function<void()> m_unsubscribe;
};
