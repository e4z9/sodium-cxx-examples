#pragma once

#include <QPushButton>

#include <sodium/sodium.h>

#include <functional>

class SQPushButton : public QPushButton
{
public:
    SQPushButton(const QString &text);
    SQPushButton(const QString &text, const sodium::cell<bool> &enabled);
    ~SQPushButton();

    const sodium::stream<sodium::unit> &sClicked() const;

private:
    std::function<void()> _enabledUnsubscribe;
    sodium::stream<sodium::unit> _sClicked;
};
