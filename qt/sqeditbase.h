#pragma once

#include <QString>
#include <QThread>
#include <QTimer>

#include <sodium/sodium.h>

template<class Base>
class SQEditBase : public Base
{
public:
    SQEditBase(const sodium::stream<QString> &sText,
               const QString &initialText,
               const sodium::cell<bool> &enabled);
    virtual ~SQEditBase();

    const sodium::cell<QString> &text() const;

protected:
    const sodium::stream_sink<QString> _sUserChangesSnk;
    std::function<void()> _unsubscribe;
    sodium::cell<QString> _text;
};

template<class Base>
SQEditBase<Base>::SQEditBase(const sodium::stream<QString> &sText,
                             const QString &initialText,
                             const sodium::cell<bool> &enabled)
    : Base(initialText)
    , _text(initialText)
{
    // Block textChanged signal handling until sText changes take effect in the GUI
    // (which is delayed by a singleShot for the not-in-main-thread case).
    // When event comes through sText, 1 is added to the accumulator,
    // when event comes through unblock, 1 is substracted.
    // sUserChanges are not passed to text cell while the accumulator is != 0
    const sodium::stream_sink<sodium::unit> unblock;
    const sodium::cell<bool> allowUserChanges
        = sText.map([](QString) { return 1; })
              .or_else(unblock.map([](sodium::unit) { return -1; }))
              .template accum<int>(0, [](int a, int b) { return a + b; })
              .map([](int c) { return c == 0; });

    _text = _sUserChangesSnk.gate(allowUserChanges).or_else(sText).hold(initialText);

    auto unsubText = sText.listen([this, unblock](const QString &s) {
        QTimer::singleShot(0, this, [this, unblock, s] {
            bool blocked = Base::blockSignals(true);
            Base::setText(s);
            Base::blockSignals(blocked);
            unblock.send({});
        });
    });

    QTimer::singleShot(0, this, [this, enabled] { Base::setEnabled(enabled.sample()); });
    auto unsubEnabled = enabled.listen([this](bool b) {
        if (QThread::currentThread() == Base::thread())
            Base::setEnabled(b);
        else
            QTimer::singleShot(0, this, [this, b] { Base::setEnabled(b); });
    });

    _unsubscribe = [unsubText, unsubEnabled] {
        if (unsubText)
            unsubText();
        if (unsubEnabled)
            unsubEnabled();
    };
}

template<class Base>
SQEditBase<Base>::~SQEditBase()
{
    if (_unsubscribe)
        _unsubscribe();
}

template<class Base>
const sodium::cell<QString> &SQEditBase<Base>::text() const
{
    return _text;
}
