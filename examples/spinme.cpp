#include "sqspinner.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

// Chapter 3.1 Listing 3.1

// see sqspinner.h and sqspinner.cpp

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
