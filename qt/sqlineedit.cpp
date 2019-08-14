#include "sqlineedit.h"

#include <QThread>
#include <QTimer>

using namespace sodium;

SQLineEdit::SQLineEdit(const QString &initialText)
    : SQLineEdit(stream<QString>(), initialText)
{}

SQLineEdit::SQLineEdit(const stream<QString> &sText, const QString &initialText)
    : QLineEdit(initialText)
    , text(initialText)
{
    // Block textChanged signal handling until sText changes take effect in the GUI
    // (which is delayed by a singleShot for the not-in-main-thread case).
    // When event comes through sText, 1 is added to the accumulator,
    // when event comes through unblock, 1 is substracted.
    // sUserChanges are not passed to text cell while the accumulator is != 0
    stream_sink<unit> unblock;
    cell<bool> allowUserChanges = sText.map([](QString) { return 1; })
                                      .or_else(unblock.map([](unit) { return -1; }))
                                      .accum<int>(0, [](int a, int b) { return a + b; })
                                      .map([](int c) { return c == 0; });

    stream_sink<QString> sUserChangesSnk;
    text = sUserChangesSnk.gate(allowUserChanges).or_else(sText).hold(initialText);
    connect(this, &QLineEdit::textChanged, [sUserChangesSnk](const QString &t) {
        sUserChangesSnk.send(t);
    });

    m_unsubscribe = sText.listen([this, unblock](const QString &s) {
        QTimer::singleShot(0, this, [this, unblock, s] {
            bool blocked = blockSignals(true);
            setText(s);
            blockSignals(blocked);
            unblock.send({});
        });
    });
}

SQLineEdit::~SQLineEdit()
{
    if (m_unsubscribe)
        m_unsubscribe();
}
