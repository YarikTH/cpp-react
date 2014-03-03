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

    for (unsigned int i = 0; i < TEST_PASSES; ++i) {

        auto var1 = var(4);
        auto var2 = var(1);
        auto var3 = var(false);
        auto rx1 = var1 * var2;
        auto rx2 = var1 + rx1;
        auto rx3 = rx1 + rx2;
        auto rx4 = rx3 == rx3;
        auto rx5 = var3.rx();

        auto test = [&] {
            cout << "var1: " << var1() << endl;
            cout << "var2: " << var2() << endl;
            cout << "var3: " << var3() << endl;
            cout << "rx1: " << rx1() << endl;
            cout << "rx2: " << rx2() << endl;
            cout << "rx3: " << rx3() << endl;
            cout << "rx4: " << rx4() << endl;
            cout << "rx5: " << rx5() << endl;

            TEST(rx1() == var1() * var2());
            TEST(rx2() == var1() + rx1());
            TEST(rx3() == rx1() + rx2());
            TEST(rx4() == (rx3() == rx3()));
            TEST(rx5() == var3());

            cout << endl;
        };

        test();

        auto change = rand() % 3;
        auto changed = 0;

        if (change) {
            cout << "var1 changed" << endl;
            var1 = rand() % TEST_RAND_LIMIT;
            changed++;
        }

        if (change) {
            cout << "var2 changed" << endl;
            var2 = rand() % TEST_RAND_LIMIT;
            changed++;
        }

        if (change || changed == 0) {
            cout << "var3 changed" << endl;
            var3 = (rand() % 2) ? true : false;
            changed++;
        }

        test();

        cout << "var freezing testing\n" << endl;

        auto dynamic_allocated_var_initializer = 4;
        cout << "allocating var4" << endl;
        auto * var4 = new Var<int>(dynamic_allocated_var_initializer);
        auto rx6 = var4->rx();
        cout << "dynamic allocated var4: " << (*var4)() << endl;
        cout << "identity rx6: " << rx6() << endl;
        cout << "deleting var4" << endl;
        delete var4;
        cout << "incrementing rx6" << endl;
        rx6 = rx6() + 1;
        cout << "updating rx6" << endl;
        rx6.updateValue();
        cout << "identity rx6 after update and var4 delete: " << rx6() << endl;
        TEST(rx6() == dynamic_allocated_var_initializer);
        cout << endl;

        cout << "var reincarnation testing\n" << endl;

        Var<int> * var5 = nullptr;
        Rx<int, int> * rx7 = nullptr;

        var5 = new Var<int>(std::move([&] {
                    cout << "creating tmp var in lambda's scope" << endl;
                    auto tmp = var(7);
                    rx7 = new Rx<int, int>([] (auto a) {
                            return a;
                        }, link(tmp));
                    cout << "rx7 value: " << (*rx7)() << endl;
                    return tmp;
                })());

        cout << "return lambdas's tmp by value" << endl;
        cout << "explicitly pass lambda's result to move contructor of var5" << endl;
        cout << "var5 value: " << (*var5)() << endl;
        cout << "rx7 value: " << (*rx7)() << endl;
        *var5 = rand() % TEST_RAND_LIMIT;
        cout << "update var5 value: " << (*var5)() << endl;
        cout << "rx7 value: " << (*rx7)() << endl;
        TEST((*var5)() == (*rx7)());
        cout << endl;

        cout << "rx reincarnation testing\n" << endl;

        Rx<int, int> * rx9 = nullptr;
        auto rx8 = new Rx<int, int>(std::move([&var5, &rx9] {
                    cout << "creating tmp rx in lambda's scope as var5 identity" << endl;
                    auto tmp = var5->rx();
                    cout << "tmp value: " << tmp() << endl;
                    cout << "allocating rx9 rx as tmp identity" << endl;
                    rx9 = new Rx<int, int>([] (auto a) {
                            return a;
                        }, link(tmp));
                    cout << "rx9 value: " << (*rx9)() << endl;
                    return tmp;
                } ()));

        cout << "return lambdas's tmp by value" << endl;
        cout << "explicitly pass lambda's result to move contructor of rx8" << endl;
        cout << "var5 value: " << (*var5)() << endl;
        cout << "rx8 value: " << (*rx8)() << endl;
        cout << "rx9 value: " << (*rx9)() << endl;
        *var5 = rand() % TEST_RAND_LIMIT;
        cout << "update var5 value: " << (*var5)() << endl;
        cout << "rx8 value: " << (*rx8)() << endl;
        cout << "rx9 value: " << (*rx9)() << endl;
        TEST((*var5)() == (*rx8)() && (*rx8)() == (*rx9)());
        cout << endl;

        cout << "rx shadowing testing\n" << endl;

        cout << "creating rx10 = var1 + var2 + var3" << endl;
        auto rx10 = var1 + var2 + var3;
        cout << "var1 = " << var1() << endl;
        cout << "var2 = " << var2() << endl;
        cout << "var3 = " << var3() << endl;
        cout << "rx10 = " << rx10() << endl;
        cout << "changing var1 to " << (var1 = (var1() + rand() % TEST_RAND_LIMIT))() << endl;
        cout << "changing var2 to " << (var2 = (var2() + rand() % TEST_RAND_LIMIT))() << endl;
        cout << "changing var3 to " << (var3 = (var3() + rand() % TEST_RAND_LIMIT))() << endl;
        cout << "rx10 = " << rx10() << endl;
        TEST(rx10() == var1() + var2() + var3());
        cout << endl;
    }

    cout << "end testing\n" << endl;

    test::Log::stats();

    return 0;
}
