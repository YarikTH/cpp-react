#include <iostream>
#include <react.hpp>

using namespace std;
using namespace react;

#define TEST(x) cout<<"testing: " #x <<((x)?": OK":": FAIL")<<endl;

int main() {
    cout << "begin testing" << endl;

    auto var0 = var(4);
    auto var1 = var0 * var0;
    auto var2 = var0 + var1;
    auto var3 = var1 + var2;
    auto var4 = var3 == var3;

    auto test = [&] {
        cout << "var0: " << var0() << endl;
        cout << "var1: " << var1() << endl;
        cout << "var2: " << var2() << endl;
        cout << "var3: " << var3() << endl;
        cout << "var4: " << var4() << endl;

        TEST(var1() == var0() * var0());
        TEST(var2() == var0() + var1());
        TEST(var3() == var1() + var2());
        TEST(var4() == (var3() == var3()));
    };

    test();

    var0 = 2;
    test();

    cout << "end testing" << endl;

    return 0;
}
