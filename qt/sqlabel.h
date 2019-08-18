#pragma once

#include <QLabel>

#include <sodium/sodium.h>

#include <functional>

class SQLabel : public QLabel
{
public:
    SQLabel(const sodium::cell<QString> &text);
    ~SQLabel();

private:
    std::function<void()> _textUnsubscribe;
};
