#include <iostream>
#include "react.hpp"

using namespace std;
using namespace react;

#define TEST(x) cout<<"testing: " #x <<((x)?": OK":": FAIL")<<endl;

int main() {
    cout << "begin testing" << endl;

    auto var0 = var(4);
    auto var1 = var0.rx([] (auto a) {
            return a * a;
        });
    auto var2 = link(var0, var1).rx([] (auto a, auto b) {
            return a + b;
        });

    auto test = [&] {
        cout << "var0: " << var0() << endl;
        cout << "var1: " << var1() << endl;
        cout << "var2: " << var2() << endl;

        TEST(var1() == var0() * var0());
        TEST(var2() == var0() + var1());
    };

    test();

    var0 = 2;
    test();

    cout << "end testing" << endl;

    return 0;
}
