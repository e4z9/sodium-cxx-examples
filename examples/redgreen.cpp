#include <sqlabel.h>
#include <sqpushbutton.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

// Chapter 2.6 Listing 2.5
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto red = new SQPushButton("red");
    auto green = new SQPushButton("green");
    stream<QString> sRed = red->sClicked.map([](unit) -> QString { return "red"; });
    stream<QString> sGreen = green->sClicked.map([](unit) -> QString { return "green"; });
    stream<QString> sColor = sRed.or_else(sGreen);
    cell<QString> color = sColor.hold("");
    auto lbl = new SQLabel(color);

    // GUI layout
    QWidget window;
    auto layout = new QVBoxLayout;
    window.setLayout(layout);
    layout->addWidget(lbl);
    layout->addWidget(red);
    layout->addWidget(green);
    layout->addStretch();
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
