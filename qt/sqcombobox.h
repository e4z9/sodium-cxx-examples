#pragma once

#include <QComboBox>
#include <QVector>

#include <boost/optional.hpp>
#include <sodium/sodium.h>

template<class T>
class SQComboBox : public QComboBox
{
public:
    struct Item
    {
        QString displayName;
        T value;
    };

    SQComboBox(const QVector<Item> &items);

    sodium::cell<boost::optional<T>> selectedItem;

private:
    boost::optional<T> valueAtIndex(int index) const;

    const QVector<Item> m_items;
};

template<class T>
SQComboBox<T>::SQComboBox(const QVector<SQComboBox::Item> &items)
    : selectedItem(boost::none)
    , m_items(items)
{
    for (const Item &item : items)
        addItem(item.displayName);

    const int index = currentIndex();
    sodium::cell_sink<boost::optional<T>> sink(valueAtIndex(index));
    QObject::connect(this,
                     QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [this, sink](int index) { sink.send(valueAtIndex(index)); });
    selectedItem = sink;
}

template<class T>
boost::optional<T> SQComboBox<T>::valueAtIndex(int index) const
{
    return index < 0 ? boost::none : boost::make_optional(m_items.at(index).value);
}
