#include <sqdatefield.h>
#include <sqpushbutton.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QFormLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

// Chapter 1.12 Listing 1.4
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto dep = new SQDateField;
    auto ret = new SQDateField;
    // Should also prevent invalid dates like Jun 31. --> left as an exercise
    const cell<bool> valid = dep->date.lift(ret->date,
                                            [](const QDate &d, const QDate &r) { return d <= r; });
    auto ok = new SQPushButton("OK", valid);

    // GUI layout
    QWidget window;
    auto layout = new QVBoxLayout;
    window.setLayout(layout);
    auto formLayout = new QFormLayout;
    formLayout->addRow(new QLabel("Departure"), dep);
    formLayout->addRow(new QLabel("Return"), ret);
    formLayout->addWidget(ok);
    layout->addLayout(formLayout);
    layout->addStretch();
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
