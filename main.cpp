#include <iostream>

#include "react.hpp"

using namespace std;
using namespace react;

int main() {
    cout << "begin testing" << endl;

    auto var = makeVar(4);
    auto square = makeRx(var, [] (int a) {
            return a * a;
        });

    cout << var << ", " << square;
    var = 2;
    cout << var << ", " << square;

    cout << "end testing" << endl;

    return 0;
}
