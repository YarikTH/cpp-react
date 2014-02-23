#include <iostream>
#include <stdlib.h>
#include <react.hpp>

using namespace std;
using namespace react;

#define TEST(x) cout<<"testing: " #x <<((x)?": OK":": FAIL")<<endl;
#define TEST_PASSES 10
#define TEST_RAND_LIMIT 10

int main() {
    srand(time(nullptr));

    cout << "begin testing\n" << endl;

    auto var01 = var(4);
    auto var02 = var(1);
    auto var1 = var01 * var02;
    auto var2 = var01 + var1;
    auto var3 = var1 + var2;
    auto var4 = var3 == var3;
    auto var5 = var4.rx();

    auto test = [&] {
        cout << "var01: " << var01() << endl;
        cout << "var02: " << var02() << endl;
        cout << "var1: " << var1() << endl;
        cout << "var2: " << var2() << endl;
        cout << "var3: " << var3() << endl;
        cout << "var4: " << var4() << endl;
        cout << "var5: " << var5() << endl;

        TEST(var1() == var01() * var02());
        TEST(var2() == var01() + var1());
        TEST(var3() == var1() + var2());
        TEST(var4() == (var3() == var3()));
        TEST(var5() == var4());

        cout << endl;
    };

    test();

    for (unsigned int i = 0; i < TEST_PASSES; ++i) {
        if (rand() % 2) {
            cout << "var01 changed" << endl;
            var01 = rand() % TEST_RAND_LIMIT;
        }
        if (rand() % 2) {
            cout << "var02 changed" << endl;
            var02 = rand() % TEST_RAND_LIMIT;
        }
        test();
    }

    cout << "end testing\n" << endl;

    return 0;
}
