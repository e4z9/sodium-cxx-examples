#include <sqlabel.h>
#include <sqlineedit.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

// Chapter 2.5 Listing 2.2
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto msg = new SQLineEdit("Hello");
    auto lbl = new SQLabel(msg->text);

    // GUI layout
    QWidget window;
    auto layout = new QVBoxLayout;
    window.setLayout(layout);
    auto formLayout = new QHBoxLayout;
    formLayout->addWidget(msg);
    formLayout->addWidget(lbl);
    lbl->setSizePolicy(QSizePolicy::Expanding, lbl->sizePolicy().verticalPolicy());
    layout->addLayout(formLayout);
    layout->addStretch();
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
