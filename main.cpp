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

        cout << "relaxed rx testing\n" << endl;

        cout << "creating relaxed rx as var * 7" << endl;
        RxRelaxed<int> rxl1 = var1.rxRelaxed([] (auto a) {
                return a * 7;
            });

        cout << "var1: " << var1() << endl;
        cout << "rxl1: " << rxl1() << endl;
        var1 = rand() % TEST_RAND_LIMIT;
        cout << "updating var1: " << var1() << endl;
        cout << "rxl1: " << rxl1() << endl;
        TEST(var1() * 7 == rxl1());
        cout << endl;

        cout << "creating Var<int> Foo::v and RxRelaxed<int> Bar::r" << endl;

        class Foo {
        public:
            Var<int> v;
        };

        class Bar {
        public:
            using VarType = int;

            Bar(const Var<VarType> & v) {
                cout << "connecting bar::r to foo::v with identity function" << endl;
                link(v).reconnect(r, [] (VarType a) {
                        return a;
                    });
            }

            void square() {
                cout << "connecting bar::r to foo::v with square function" << endl;
                r.setFn([] (VarType a) {
                        return a * a;
                    });
            }

            void identity() {
                cout << "connecting bar::r to foo::v with identity function" << endl;
                r.setFn([] (VarType a) {
                        return a;
                    });
            }

            RxRelaxed<int> r;
        };

        Foo f;
        Bar b(f.v);

        cout << "foo::v " << f.v() << endl;
        cout << "bar::r " << b.r() << endl;
        f.v = rand() % TEST_RAND_LIMIT;
        cout << "updating foo::v " << f.v() << endl;
        cout << "bar::r " << b.r() << endl;
        TEST(f.v() == b.r());
        b.square();
        cout << "foo::v " << f.v() << endl;
        cout << "bar::r " << b.r() << endl;
        TEST(f.v() * f.v() == b.r());
        b.identity();
        cout << "foo::v " << f.v() << endl;
        cout << "bar::r " << b.r() << endl;
        TEST(f.v() == b.r());
        cout << endl;

        cout << "setFn() testing\n" << endl;
        cout << "creating rx11 as var6 identity" << endl;
        auto var6 = var(rand() % TEST_RAND_LIMIT);
        auto rx11 = var6.rx();
        cout << "var6 value: " << var6() << endl;
        cout << "rx11 value: " << rx11() << endl;
        TEST(var6() == rx11());
        cout << "change rx11 function to square" << endl;
        rx11.setFn([] (auto a) {
                return a * a;
            });
        cout << "var6 value: " << var6() << endl;
        cout << "rx11 value: " << rx11() << endl;
        TEST(var6() * var6() == rx11());
        cout << endl;
    }

    cout << "end testing\n" << endl;

    test::Log::stats();

    return 0;
}
