#pragma once

#include <sqcombobox.h>

#include <QDate>
#include <QWidget>

#include <sodium/sodium.h>

class SQDateField : public QWidget
{
public:
    SQDateField();

    const sodium::cell<QDate> &date() const;

private:
    SQComboBox<int> *_year = nullptr;
    SQComboBox<int> *_month = nullptr;
    SQComboBox<int> *_day = nullptr;
    sodium::cell<QDate> _date;
};
