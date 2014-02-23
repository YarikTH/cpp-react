#ifndef LINEARVAR_HPP
#define LINEARVAR_HPP

#include "link.hpp"

namespace react {

    // arithmetic

    template <class T1, class T2>
    auto operator+(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a + b;
            });
    }

    template <class T1, class T2>
    auto operator-(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a - b;
            });
    }

    template <class T1>
    auto operator+(const Var<T1> & v) {
        return link(v).rx([] (auto & a) {
                return +a;
            });
    }

    template <class T1>
    auto operator-(const Var<T1> & v) {
        return link(v).rx([] (auto & a) {
                return -a;
            });
    }

    template <class T1, class T2>
    auto operator*(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a * b;
            });
    }

    template <class T1, class T2>
    auto operator/(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a / b;
            });
    }

    template <class T1, class T2>
    auto operator%(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a % b;
            });
    }

    // comparison

    template <class T1, class T2>
    auto operator==(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a == b;
            });
    }

    template <class T1, class T2>
    auto operator!=(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a != b;
            });
    }

    template <class T1, class T2>
    auto operator>(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a > b;
            });
    }

    template <class T1, class T2>
    auto operator<(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a < b;
            });
    }

    template <class T1, class T2>
    auto operator>=(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a >= b;
            });
    }

    template <class T1, class T2>
    auto operator<=(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a <= b;
            });
    }

    // logical

    template <class T1>
    auto operator!(const Var<T1> & v) {
        return link(v).rx([] (auto & a) {
                return !a;
            });
    }

    template <class T1, class T2>
    auto operator&&(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a && b;
            });
    }

    template <class T1, class T2>
    auto operator||(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a || b;
            });
    }

    // bitwise

    template <class T1>
    auto operator~(const Var<T1> & v) {
        return link(v).rx([] (auto & a) {
                return ~a;
            });
    }

    template <class T1, class T2>
    auto operator&(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a & b;
            });
    }

    template <class T1, class T2>
    auto operator|(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a | b;
            });
    }

    template <class T1, class T2>
    auto operator^(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a & b;
            });
    }

    template <class T1, class T2>
    auto operator<<(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a << b;
            });
    }

    template <class T1, class T2>
    auto operator>>(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a >> b;
            });
    }

    // other

    template <class T1, class T2>
    auto operator,(const Var<T1> & v1, const Var<T2> & v2) {
        return link(v1, v2).rx([] (auto & a, auto & b) {
                return a , b;
            });
    }

}

#endif // LINEARVAR_HPP
