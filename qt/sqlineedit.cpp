#include "sqlineedit.h"

#include <QThread>
#include <QTimer>

using namespace sodium;

SQLineEdit::SQLineEdit(const QString &initialText)
    : SQLineEdit(stream<QString>(), initialText)
{}

SQLineEdit::SQLineEdit(const stream<QString> &sText, const QString &initialText)
    : SQLineEdit(sText, initialText, true)
{}

SQLineEdit::SQLineEdit(const QString &initialText, const cell<bool> &enabled)
    : SQLineEdit(stream<QString>(), initialText, enabled)
{}

SQLineEdit::SQLineEdit(const sodium::stream<QString> &sText,
                       const QString &initialText,
                       const sodium::cell<bool> &enabled)
    : SQEditBase<QLineEdit>(sText, initialText, enabled)
{
    connect(this, &QLineEdit::textChanged, [this](const QString &t) { _sUserChangesSnk.send(t); });
}
