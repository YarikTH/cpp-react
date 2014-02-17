#pragma once

#ifndef RXLINK_HPP
#define RXLINK_HPP

#include <tuple/tuple.hpp>

namespace react {

    template <class T, class FN, class ... TS>
    class RxLink {
    public:
        using Tuple = tuple::Tuple<const Var<TS> * ...>;

        RxLink() = default;
        RxLink(const Tuple & newVars):
            vars(newVars) {
        }
        RxLink(Tuple && newVars):
            vars(std::move(newVars)) {
        }
        RxLink(const Var<TS> * ... newVars):
            vars(newVars ...){
        }
        RxLink(const Var<TS> & ... newVars):
            vars(&newVars ...){
        }

        Tuple vars;

    private:
    };

}

#endif // RXLINK_HPP
