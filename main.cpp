#include <iostream>

#include "react.hpp"

using namespace std;
using namespace react;

int main() {
    cout << "begin testing" << endl;

    auto var0 = makeVar(4);
    auto var1 = makeVar(var0, [] (auto a) {
            return a * a;
        });

    cout << "id0 " << var0.getId() << endl;
    cout << "id1 " << var1.getId() << endl;

    cout << var0 << ", " << var1 << endl;
    var0 = 2;
    cout << var0 << ", " << var1 << endl;

    cout << "end testing" << endl;

    return 0;
}
