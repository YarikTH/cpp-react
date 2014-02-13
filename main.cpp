#include <iostream>

#include "react.hpp"

using namespace std;
using namespace react;

int main() {
    cout << "begin testing" << endl;

    auto var = makeVar(4);
    auto square = makeRx(var, [] (auto a) {
            return a * a;
        });

    cout << var << ", " << square << endl;
    var = 2;
    cout << var << ", " << square << endl;

    cout << "end testing" << endl;

    return 0;
}
