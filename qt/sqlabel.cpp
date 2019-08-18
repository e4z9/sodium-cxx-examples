#include "sqlabel.h"

#include <QThread>
#include <QTimer>

using namespace sodium;

SQLabel::SQLabel(const sodium::cell<QString> &text)
{
    _textUnsubscribe = text.listen([this](const QString &t) {
        if (QThread::currentThread() == thread())
            setText(t);
        else
            QTimer::singleShot(0, this, [this, t] { setText(t); });
    });
    QTimer::singleShot(0, this, [this, text] { setText(text.sample()); });
}

SQLabel::~SQLabel()
{
    if (_textUnsubscribe)
        _textUnsubscribe();
}
