#include <sodium/sodium.h>

#include <iostream>

using namespace std;
using namespace sodium;

template<typename A>
class Promise
{
public:
    Promise(stream<A> sDeliver);

    stream<A> then();

    // imperative interface to "then"
    void thenDo(const function<void(A)> &handler);

    const stream<A> &sDeliver() const;
    const cell<boost::optional<A>> &oValue() const;

private:
    stream<A> _sDeliver;
    cell<boost::optional<A>> _oValue;
};

template<typename A>
Promise<A>::Promise(stream<A> sDeliver)
    : _sDeliver(sDeliver.once())
    , _oValue(_sDeliver.map([](const A &a) { return boost::make_optional(a); }).hold(boost::none))
{}

template<typename A>
stream<A> Promise<A>::then()
{
    return filter_optional(_oValue.value()).or_else(_sDeliver).once();
}

template<typename A>
void Promise<A>::thenDo(const function<void(A)> &handler)
{
    transaction t;
    then().listen_once(handler);
}

template<typename A>
const stream<A> &Promise<A>::sDeliver() const
{
    return _sDeliver;
}

template<typename A>
const cell<boost::optional<A>> &Promise<A>::oValue() const
{
    return _oValue;
}

// Chapter 11.2 Listing 11.4, 11.5
int main()
{
    {
        stream_sink<string> s;
        Promise<string> p(s);
        s.send("early");
        p.thenDo([](const string &s) { cout << s << endl; });
    }
    {
        stream_sink<string> s;
        Promise<string> p(s);
        p.thenDo([](const string &s) { cout << s << endl; });
        s.send("late");
    }
    return 0;
}
