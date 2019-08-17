#include <sqlabel.h>
#include <sqpushbutton.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

// Chapter 2.9 Listing 2.7
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;

    {
        // explicitly wrap in transaction
        transaction trans; // closes automatically when it goes out of scope
        cell_loop<int> value;
        auto lblValue = new SQLabel(value.map([](int i) { return QString::number(i); }));
        auto plus = new SQPushButton("+");
        auto minus = new SQPushButton("-");
        const stream<int> sPlusDelta = plus->sClicked.map([](unit) { return 1; });
        const stream<int> sMinusDelta = minus->sClicked.map([](unit) { return -1; });
        const stream<int> sDelta = sPlusDelta.or_else(sMinusDelta);
        const stream<int> sUpdate = sDelta.snapshot(value, [](int d, int v) { return v + d; });
        value.loop(sUpdate.hold(0));

        // GUI layout
        auto layout = new QVBoxLayout;
        window.setLayout(layout);
        auto formLayout = new QHBoxLayout;
        formLayout->addWidget(lblValue);
        lblValue->setFixedWidth(30);
        formLayout->addWidget(plus);
        formLayout->addWidget(minus);
        formLayout->addStretch();
        layout->addLayout(formLayout);
        layout->addStretch();
    }
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
