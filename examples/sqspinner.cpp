#include "sqspinner.h"

#include <sqlineedit.h>
#include <sqpushbutton.h>

#include <QHBoxLayout>
#include <QVBoxLayout>

using namespace sodium;

SQSpinner::SQSpinner(int initialValue)
    : _value(initialValue)
{
    stream_loop<int> sSetValue;
    auto textField = new SQLineEdit(sSetValue.map([](int v) { return QString::number(v); }),
                                    QString::number(initialValue));
    _value = textField->text().map([](const QString &s) { return s.toInt(); });
    auto plus = new SQPushButton("+");
    auto minus = new SQPushButton("-");
    const stream<int> sPlusDelta = plus->sClicked().map([](unit) { return 1; });
    const stream<int> sMinusDelta = minus->sClicked().map([](unit) { return -1; });
    const stream<int> sDelta = sPlusDelta.or_else(sMinusDelta);
    sSetValue.loop(sDelta.snapshot(_value, [](int d, int v) { return v + d; }));

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

const sodium::cell<int> &SQSpinner::value() const
{
    return _value;
}
