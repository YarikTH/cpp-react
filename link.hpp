#pragma once

#ifndef LINK_HPP
#define LINK_HPP

#include <tuple/tuple.hpp>

namespace react {

    template <class T, class FN, class ... TS>
    class Link {
    public:
        using Tuple = tuple::Tuple<const Var<TS> * ...>;

        Link() = default;
        Link(const Tuple & newVars):
            vars(newVars) {
        }
        Link(Tuple && newVars):
            vars(std::move(newVars)) {
        }
        Link(const Var<TS> * ... newVars):
            vars(newVars ...){
        }
        Link(const Var<TS> & ... newVars):
            vars(&newVars ...){
        }

        Tuple vars;

    private:
    };

}

#endif // LINK_HPP
