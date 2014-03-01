#pragma once

#ifndef LINK_HPP
#define LINK_HPP

#include <tuple/tuple.hpp>
#include "rx.hpp"

namespace react {

    template <class T, class ... TS>
    class Rx;

    template <class ... TS>
    class Link {
    public:
        using Tuple = tuple::Tuple<const Var<TS> * ...>;

        Link() = default;

        Link(const Link & l):
            vars(l.vars) {
        }

        Link(Link && l):
            vars(std::move(l.vars)) {
        }

        Link(const Tuple & newVars):
            vars(newVars) {
        }

        Link(Tuple && newVars):
            vars(std::move(newVars)) {
        }

        Link(const Var<TS> & ... newVars):
            vars(&newVars ...){
        }

        Link & operator=(const Link & l) {
            vars = l.vars;
            return *this;
        }

        Link & operator=(Link && l) {
            vars = std::move(l.vars);
            return *this;
        }

        const auto & getVars() const {
            return vars;
        }

        template <class FN>
        auto rx(FN && f) {
            using RxType = Rx<decltype(f(ref<TS>() ...)), TS ...>;
            return RxType(std::forward<FN>(f), *this);
        }

    private:
        template <class T>
        static auto & ref() {
            return *static_cast<T *>(nullptr);
        }

        Tuple vars;
    };

    template <class ... TS>
    auto link(const Var<TS> & ... newVars) {
        return Link<TS ...>(newVars ...);
    }

}

#endif // LINK_HPP
