#pragma once

#include <QWidget>

#include <sodium/sodium.h>

class SQSpinner : public QWidget
{
public:
    SQSpinner(int initialValue);

    sodium::cell<int> value;
};
