#include <sqlineedit.h>
#include <sqpushbutton.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

// Chapter 3.1 Listing 3.1

class SQSpinner : public QWidget
{
public:
    SQSpinner(int initialValue);

    cell<int> value;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;
    auto spinner = new SQSpinner(0);
    auto layout = new QVBoxLayout;
    window.setLayout(layout);
    auto formLayout = new QHBoxLayout;
    formLayout->addStretch();
    formLayout->addWidget(spinner);
    formLayout->addStretch();
    layout->addLayout(formLayout);
    layout->addStretch(1);
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}

SQSpinner::SQSpinner(int initialValue)
    : value(initialValue)
{
    stream_loop<int> sSetValue;
    auto textField = new SQLineEdit(sSetValue.map([](int v) { return QString::number(v); }),
                                    QString::number(initialValue));
    value = textField->text.map([](const QString &s) { return s.toInt(); });
    auto plus = new SQPushButton("+");
    auto minus = new SQPushButton("-");
    stream<int> sPlusDelta = plus->sClicked.map([](unit) { return 1; });
    stream<int> sMinusDelta = minus->sClicked.map([](unit) { return -1; });
    stream<int> sDelta = sPlusDelta.or_else(sMinusDelta);
    sSetValue.loop(sDelta.snapshot(value, [](int d, int v) { return v + d; }));

    // GUI layout
    auto layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(layout);
    auto buttonLayout = new QVBoxLayout;
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setSpacing(0);
    buttonLayout->setSizeConstraint(QLayout::SetFixedSize);
    buttonLayout->addWidget(plus);
    buttonLayout->addWidget(minus);
    layout->addWidget(textField);
    layout->addLayout(buttonLayout);

    textField->setFixedWidth(50);
}
