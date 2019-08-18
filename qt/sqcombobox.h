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

    const sodium::cell<boost::optional<T>> &selectedItem() const;

private:
    boost::optional<T> valueAtIndex(int index) const;

    const QVector<Item> _items;
    sodium::cell<boost::optional<T>> _selectedItem;
};

template<class T>
SQComboBox<T>::SQComboBox(const QVector<SQComboBox::Item> &items)
    : _selectedItem(boost::none)
    , _items(items)
{
    for (const Item &item : items)
        addItem(item.displayName);

    const int index = currentIndex();
    sodium::cell_sink<boost::optional<T>> sink(valueAtIndex(index));
    QObject::connect(this,
                     QOverload<int>::of(&QComboBox::currentIndexChanged),
                     [this, sink](int index) { sink.send(valueAtIndex(index)); });
    _selectedItem = sink;
}

template<class T>
const sodium::cell<boost::optional<T>> &SQComboBox<T>::selectedItem() const
{
    return _selectedItem;
}

template<class T>
boost::optional<T> SQComboBox<T>::valueAtIndex(int index) const
{
    return index < 0 ? boost::none : boost::make_optional(_items.at(index).value);
}
