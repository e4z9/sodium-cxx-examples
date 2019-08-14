#include "sqlineedit.h"

#include <QThread>
#include <QTimer>

SQLineEdit::SQLineEdit(const sodium::stream<QString> &sText, const QString &initialText)
    : QLineEdit(initialText)
    , text(sText.hold(initialText))
{
    m_unsubscribe = sText.listen([this](const QString &s) {
        if (QThread::currentThread() == thread())
            setText(s);
        else
            QTimer::singleShot(0, this, [this, s] { setText(s); });
    });
}

SQLineEdit::~SQLineEdit()
{
    if (m_unsubscribe)
        m_unsubscribe();
}
