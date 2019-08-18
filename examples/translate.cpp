#include <sqlabel.h>
#include <sqlineedit.h>
#include <sqpushbutton.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QLabel>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

// Chapter 2.7 Listing 2.6
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto english = new SQLineEdit("I like FRP");
    auto translate = new SQPushButton("Translate");
    const stream<QString> sLatin = translate->sClicked()
                                       .snapshot(english->text(), [](unit, const QString &text) {
                                           QString result = text.trimmed();
                                           result.replace(QRegularExpression("\\s+|$"), "us ");
                                           return result.trimmed();
                                       });
    const cell<QString> latin = sLatin.hold("");
    auto lblLatin = new SQLabel(latin);

    // GUI layout
    QWidget window;
    auto layout = new QVBoxLayout;
    window.setLayout(layout);
    layout->addWidget(english);
    layout->addWidget(translate);
    layout->addWidget(lblLatin);
    layout->addStretch();
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
