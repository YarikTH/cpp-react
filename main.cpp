#include <iostream>
#include <string>
#include <stdlib.h>
#include <react.hpp>
#include <test.hpp>

using namespace std;
using namespace react;

#define TEST(x) test::Log::log(#x, (x) ? 0 : 1);
#define TEST_PASSES 3
#define TEST_RAND_LIMIT 10

int main() {
    srand(time(nullptr));

    cout << "begin testing\n" << endl;

    auto var01 = var(4);
    auto var02 = var(1);
    auto var03 = var(false);
    auto var1 = var01 * var02;
    auto var2 = var01 + var1;
    auto var3 = var1 + var2;
    auto var4 = var3 == var3;
    auto var5 = var03.rx();

    auto test = [&] {
        cout << "var01: " << var01() << endl;
        cout << "var02: " << var02() << endl;
        cout << "var03: " << var03() << endl;
        cout << "var1: " << var1() << endl;
        cout << "var2: " << var2() << endl;
        cout << "var3: " << var3() << endl;
        cout << "var4: " << var4() << endl;
        cout << "var5: " << var5() << endl;

        TEST(var1() == var01() * var02());
        TEST(var2() == var01() + var1());
        TEST(var3() == var1() + var2());
        TEST(var4() == (var3() == var3()));
        TEST(var5() == var03());

        cout << endl;
    };

    test();

    for (unsigned int i = 0; i < TEST_PASSES; ++i) {
        auto change = rand() % 3;
        auto changed = 0;

        if (change) {
            cout << "var01 changed" << endl;
            var01 = rand() % TEST_RAND_LIMIT;
            changed++;
        }

        if (change) {
            cout << "var02 changed" << endl;
            var02 = rand() % TEST_RAND_LIMIT;
            changed++;
        }

        if (change || changed == 0) {
            cout << "var03 changed" << endl;
            var03 = (rand() % 2) ? true : false;
            changed++;
        }

        test();
    }

    cout << "var freezing testing\n" << endl;

    auto dynamic_allocated_var_initializer = 4;
    cout << "allocating var04" << endl;
    auto * var04 = new Var<int>(dynamic_allocated_var_initializer);
    auto var6 = var04->rx();
    cout << "dynamic allocated var04: " << (*var04)() << endl;
    cout << "identity var6: " << var6() << endl;
    cout << "deleting var04" << endl;
    delete var04;
    cout << "incrementing var6" << endl;
    var6 = var6() + 1;
    cout << "updating var6" << endl;
    var6.updateValue();
    cout << "identity var6 after update and var04 delete: " << var6() << endl;
    TEST(var6() == dynamic_allocated_var_initializer);
    cout << endl;

    cout << "var reincornation testing\n" << endl;

    Var<int> * var05 = nullptr;
    Rx<int, std::function<int(int)>, int> * var7 = nullptr;

    var05 = new Var<int>(std::move([&] {
                cout << "creating tmp var in lambda's scope" << endl;
                auto tmp = var(7);
                cout << "tmp value: " << tmp() << endl;
                cout << "allocating var7 rx as tmp identity" << endl;
                var7 = new Rx<int, std::function<int(int)>, int>([] (auto a) {
                        return a;
                    }, link(tmp));
                cout << "var7 value: " << (*var7)() << endl;
                return tmp;
            })());

    cout << "return lambdas's tmp by value" << endl;
    cout << "explicitly pass lambda's result to move contructor of var05" << endl;
    cout << "var05 value: " << (*var05)() << endl;
    cout << "var7 value: " << (*var7)() << endl;
    *var05 = 8;
    cout << "update var05 value: " << (*var05)() << endl;
    cout << "var7 value: " << (*var7)() << endl;
    TEST((*var05)() == (*var7)());
    cout << endl;

    cout << "rx reincornation testing\n" << endl;

    for (auto i = 0; i < TEST_PASSES; ++i) {
        cout << "creating var8 = var01 + var02 + var03" << endl;
        auto var8 = var01 + var02 + var03;
        cout << "var01 = " << var01() << endl;
        cout << "var02 = " << var02() << endl;
        cout << "var03 = " << var03() << endl;
        cout << "var8 = " << var8() << endl;
        cout << "changing var01 to " << (var01 = (var01() + rand() % TEST_RAND_LIMIT))() << endl;
        cout << "changing var02 to " << (var02 = (var02() + rand() % TEST_RAND_LIMIT))() << endl;
        cout << "changing var03 to " << (var03 = (var03() + rand() % TEST_RAND_LIMIT))() << endl;
        cout << "var8 = " << var8() << endl;
        TEST(var8() == var01() + var02() + var03());
        cout << endl;
    }

    cout << "end testing\n" << endl;

    test::Log::stats();

    return 0;
}
