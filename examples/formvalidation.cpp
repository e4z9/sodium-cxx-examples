#include "sqspinner.h"

#include <sqlabel.h>
#include <sqlineedit.h>
#include <sqpushbutton.h>

#include <sodium/sodium.h>

#include <QApplication>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QWidget>

using namespace sodium;

// Chapter 3.2 Listing 3.2
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget window;

    {
        transaction t; // wrap in explicit transaction, closes when transaction goes out of scope
        static const int maxEmails = 4;
        struct Field
        {
            QLabel *label;
            QWidget *field;
            cell<QString> error;
        };
        std::vector<Field> fields;
        fields.reserve(maxEmails + 2);

        auto name = new SQLineEdit("");
        fields.push_back(
            {new QLabel("Name"), name, name->text().map([](const QString &s) -> QString {
                 return s.trimmed().isEmpty()
                            ? "<-- enter something"
                            : !s.trimmed().contains(' ') ? "<-- must contain space" : "";
             })});

        auto number = new SQSpinner(1);
        fields.push_back({new QLabel("No of email addresses"), number, number->value().map([](int n) {
                              return n < 1 || n > maxEmails
                                         ? QString("<-- must be 1 to %1").arg(maxEmails)
                                         : QString();
                          })});

        for (int i = 0; i < maxEmails; ++i) {
            const cell<bool> enabled = number->value().map([i](int n) { return i < n; });
            auto email = new SQLineEdit("", enabled);
            fields.push_back(
                {new QLabel(QString("Email #%1").arg(i + 1)),
                 email,
                 email->text().lift(number->value(), [i](const QString &s, int n) -> QString {
                     return i >= n ? ""
                                   : s.trimmed().isEmpty()
                                         ? "<-- enter something"
                                         : !s.contains('@') ? "<-- must contain @" : "";
                 })});
        }

        cell<bool> allValid(true);
        for (const Field &field : fields) {
            const cell<bool> thisValid = field.error.map(
                [](const QString &s) { return s.isEmpty(); });
            allValid = allValid.lift(thisValid, [](bool a, bool b) { return a && b; });
        }
        auto ok = new SQPushButton("Ok", allValid);

        // GUI layout
        auto layout = new QVBoxLayout;
        window.setLayout(layout);
        auto formLayout = new QGridLayout;
        int row = 0;
        for (const Field &field : fields) {
            formLayout->addWidget(field.label, row, 0);
            formLayout->addWidget(field.field, row, 1);
            auto errorLabel = new SQLabel(field.error);
            errorLabel->setSizePolicy(QSizePolicy::Expanding,
                                      errorLabel->sizePolicy().verticalPolicy());
            formLayout->addWidget(errorLabel, row, 2);
            ++row;
        }
        formLayout->addWidget(ok, row, 1);
        layout->addLayout(formLayout);
        layout->addStretch();
    }
    window.setGeometry(100, 100, 500, 500);
    window.show();
    return app.exec();
}
