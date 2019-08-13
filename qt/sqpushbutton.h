#pragma once

#include <QPushButton>

#include <sodium/sodium.h>

#include <functional>

class SQPushButton : public QPushButton
{
public:
    SQPushButton(const QString &text, const sodium::cell<bool> &enabled);
    ~SQPushButton();

    sodium::stream<sodium::unit> sClicked;

private:
    std::function<void()> m_enabledUnsubscribe;
};
