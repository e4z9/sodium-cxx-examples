#include "sqpushbutton.h"

#include <QThread>
#include <QTimer>

using namespace sodium;

SQPushButton::SQPushButton(const QString &text)
    : SQPushButton(text, true)
{}

SQPushButton::SQPushButton(const QString &text, const cell<bool> &enabled)
    : QPushButton(text)
{
    const stream_sink<unit> sClickedSink;
    QObject::connect(this, &QPushButton::clicked, [sClickedSink] { sClickedSink.send(unit()); });
    sClicked = sClickedSink;

    m_enabledUnsubscribe = enabled.listen([this](bool b) {
        if (QThread::currentThread() == thread())
            setEnabled(b);
        else
            QTimer::singleShot(0, this, [this, b] { setEnabled(b); });
    });
    QTimer::singleShot(0, this, [this, enabled] { setEnabled(enabled.sample()); });
}

SQPushButton::~SQPushButton()
{
    if (m_enabledUnsubscribe)
        m_enabledUnsubscribe();
}
