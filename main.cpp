#include <iostream>

#include "var.hpp"
#include "rx.hpp"

using namespace std;
using namespace react;

int main() {
    cout << "begin testing" << endl;

    auto var0 = makeVar(4);
    auto var1 = makeRx(var0, [] (auto a) {
            return a * a;
        });
    auto var2 = makeRx([] (auto a, auto b) {
            return a + b;
        }, var0, var1);

    cout << "id0 " << var0.getId() << endl;
    cout << "id1 " << var1.getId() << endl;
    cout << "id2 " << var2.getId() << endl;

    cout << var0() << ", " << var1() << ", " << var2() << endl;
    var0 = 2;
    cout << var0() << ", " << var1() << ", " << var2() << endl;

    cout << "end testing" << endl;

    return 0;
}
