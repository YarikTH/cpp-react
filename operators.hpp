/*

  react LGPL Source Code
  Copyright (C) 2014 Edward Knyshov

  This file is part of the react LGPL Source Code (react Source Code).

  react Source Code is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  react Source Code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with react Source Code. If not, see <http://www.gnu.org/licenses/>

*/

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
