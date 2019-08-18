#include <sqdatefield.h>
#include <sqpushbutton.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QFormLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

class Rule
{
public:
    Rule(std::function<bool(QDate, QDate)> f)
        : f(f)
    {}

    cell<bool> reify(const cell<QDate> &dep, const cell<QDate> &ret) { return dep.lift(ret, f); }

    Rule andRule(Rule other)
    {
        return {[this, other](const QDate &a, const QDate &b) { return f(a, b) && other.f(a, b); }};
    }

private:
    std::function<bool(QDate, QDate)> f;
};

// Chapter 1.17 Listing 1.6
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto dep = new SQDateField;
    auto ret = new SQDateField;
    // Should also prevent invalid dates like Jun 31. --> left as an exercise
    const auto unlucky = [](const QDate &d) {
        return d.day() == 4 || d.day() == 14 || d.day() == 24;
    };
    Rule r1([](const QDate &d, const QDate &r) { return d <= r; });
    Rule r2([unlucky](const QDate &d, const QDate &r) { return !unlucky(d) && !unlucky(r); });
    Rule r = r1.andRule(r2);
    const cell<bool> valid = r.reify(dep->date(), ret->date());
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
