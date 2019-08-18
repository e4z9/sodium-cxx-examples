#pragma once

#include <QWidget>

#include <sodium/sodium.h>

class SQSpinner : public QWidget
{
public:
    SQSpinner(int initialValue);

    const sodium::cell<int> &value() const;

private:
    sodium::cell<int> _value;
};
