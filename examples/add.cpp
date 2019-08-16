#include <sqlabel.h>
#include <sqlineedit.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>

#include <algorithm>

using namespace sodium;

// Chapter 2.11 Listing 2.8
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto txtA = new SQLineEdit("5");
    auto txtB = new SQLineEdit("10");
    cell<int> a = txtA->text.map([](const QString &s) { return s.toInt(); });
    cell<int> b = txtB->text.map([](const QString &s) { return s.toInt(); });
    cell<int> sum = a.lift(b, [](int a, int b) { return a + b; });
    auto lblSum = new SQLabel(sum.map([](int s) { return QString::number(s); }));

    // GUI layout
    QWidget window;
    auto layout = new QVBoxLayout;
    window.setLayout(layout);
    layout->addWidget(txtA);
    layout->addWidget(txtB);
    layout->addWidget(lblSum);
    layout->addStretch();
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
