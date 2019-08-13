#include "sqdatefield.h"

#include <QHBoxLayout>

SQDateField::SQDateField()
    : date(QDate::currentDate())
{
    const QDate now = QDate::currentDate();

    QVector<SQComboBox<int>::Item> years;
    for (int i = now.year() - 10; i <= now.year() + 10; ++i)
        years.append({QString::number(i), i});
    year = new SQComboBox<int>(years);
    year->setCurrentIndex(10);

    static const QString monthNames[]
        = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dez"};
    QVector<SQComboBox<int>::Item> months;
    for (int i = 0; i < 12; ++i)
        months.append({monthNames[i], i + 1});
    month = new SQComboBox<int>(months);
    month->setCurrentIndex(now.month() - 1);

    QVector<SQComboBox<int>::Item> days;
    for (int i = 1; i <= 31; ++i)
        days.append({QString::number(i), i});
    day = new SQComboBox<int>(days);
    day->setCurrentIndex(now.day() - 1);

    date = year->selectedItem.lift(month->selectedItem,
                                   day->selectedItem,
                                   [](boost::optional<int> year,
                                      boost::optional<int> month,
                                      boost::optional<int> day) {
                                       if (year && month && day)
                                           return QDate(*year, *month, *day);
                                       return QDate();
                                   });

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    layout->addWidget(year);
    layout->addWidget(month);
    layout->addWidget(day);
}
