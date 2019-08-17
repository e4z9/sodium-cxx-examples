#include <sodium/sodium.h>

#include <iostream>

using namespace std;
using namespace sodium;

// Chapter 6.4 Listing 6.11
int main()
{
    const cell_sink<int> ones(1);
    const cell<int> hundreds = ones.map([](int i) { return i * 100; });
    const cell<int> sum = ones.lift(hundreds, [](int a, int b) { return a + b; });
    auto unlisten = sum.listen([](int i) { cerr << i << endl; });
    ones.send(2);
    unlisten();
    return 0;
}
