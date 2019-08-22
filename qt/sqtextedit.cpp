#include "sqtextedit.h"

#include <QThread>
#include <QTimer>

using namespace sodium;

SQTextEdit::SQTextEdit(const QString &initialText)
    : SQTextEdit(stream<QString>(), initialText)
{}

SQTextEdit::SQTextEdit(const stream<QString> &sText, const QString &initialText)
    : SQTextEdit(sText, initialText, true)
{}

SQTextEdit::SQTextEdit(const QString &initialText, const cell<bool> &enabled)
    : SQTextEdit(stream<QString>(), initialText, enabled)
{}

SQTextEdit::SQTextEdit(const sodium::stream<QString> &sText,
                       const QString &initialText,
                       const sodium::cell<bool> &enabled)
    : SQEditBase<QTextEdit>(sText, initialText, enabled)
{
    connect(this, &SQTextEdit::textChanged, [this]() { _sUserChangesSnk.send(toPlainText()); });
}
