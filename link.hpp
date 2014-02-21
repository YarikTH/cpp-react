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

        Link(const Link & link):
            vars(link.vars) {
        }

        Link(Link && link):
            vars(std::move(link.vars)) {
        }

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

        Link & operator=(const Link & link) {
            vars = link.vars;
            return *this;
        }

        Link & operator=(Link && link) {
            vars = std::move(link.vars);
            return *this;
        }

        const auto & getVars() const {
            return vars;
        }

    private:
        Tuple vars;
    };

    template <class T, class FN, class ... TS>
    auto link(const Var<TS> * ... newVars) {
        return Link<T, FN, TS ...>(newVars ...);
    }

    template <class T, class FN, class ... TS>
    auto link(const Var<TS> & ... newVars) {
        return Link<T, FN, TS ...>(newVars ...);
    }

}

#endif // LINK_HPP
