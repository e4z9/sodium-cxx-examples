#include <sodium/sodium.h>

#include <iostream>
#include <string>

using namespace std;
using namespace sodium;

template <typename T>
T transactionRun(const function<T()> &action)
{
    transaction t;
    const T &result = action();
    t.close();
    return result;
}

// Chapter 8.3 Listing 8.3
int main()
{
    stream_sink<int> sX;
    stream<int> sXPlus1 = sX.map([](int i) { return i + 1; });
    const auto unsubscribe = transactionRun<function<void()>>([&sX, &sXPlus1] {
        sX.send(1);
        return sXPlus1.listen([](int i) { cout << to_string(i) << endl; });
    });
    sX.send(2);
    sX.send(3);
    unsubscribe();
    return 0;
}
