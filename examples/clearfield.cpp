#include <sqlineedit.h>
#include <sqpushbutton.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

// Chapter 2.1 Listing 2.1
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto clear = new SQPushButton("Clear");
    stream<QString> sClearIt = clear->sClicked.map([](unit) { return QString(); });
    auto text = new SQLineEdit(sClearIt, "Hello");

    // GUI layout
    QWidget window;
    auto layout = new QVBoxLayout;
    window.setLayout(layout);
    auto formLayout = new QHBoxLayout;
    formLayout->addWidget(text);
    formLayout->addWidget(clear);
    formLayout->addStretch();
    layout->addLayout(formLayout);
    layout->addStretch();
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
