#include <sqlineedit.h>
#include <sqpushbutton.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

// Chapter 2.6 Listing 2.4
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto onegai = new SQPushButton("Onegai shimasu");
    auto thanks = new SQPushButton("Thank you");
    const stream<QString> sOnegai = onegai->sClicked().map(
        [](unit) -> QString { return "Onegai shimasu"; });
    const stream<QString> sThanks = thanks->sClicked().map(
        [](unit) -> QString { return "Thank you"; });
    const stream<QString> sCanned = sOnegai.or_else(sThanks);
    auto text = new SQLineEdit(sCanned, "");

    // GUI layout
    QWidget window;
    auto layout = new QVBoxLayout;
    window.setLayout(layout);
    layout->addWidget(text);
    layout->addWidget(onegai);
    layout->addWidget(thanks);
    layout->addStretch();
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
