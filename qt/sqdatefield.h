#pragma once

#include <sqcombobox.h>

#include <QDate>
#include <QWidget>

#include <sodium/sodium.h>

class SQDateField : public QWidget
{
public:
    SQDateField();

    sodium::cell<QDate> date;

private:
    SQComboBox<int> *year = nullptr;
    SQComboBox<int> *month = nullptr;
    SQComboBox<int> *day = nullptr;
};
