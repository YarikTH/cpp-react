#pragma once

#ifndef RXDISPATCHER_HPP
#define RXDISPATCHER_HPP

#include "vardispatcher.hpp"
#include "rxlink.hpp"
#include <unordered_map>

namespace react {

    template <class T>
    class Var;

    template <class T, class FN, class ... TS>
    class Rx;

    template <class T, class FN, class ... TS>
    class RxDispatcher {
    public:
        using Rx = Rx<T, FN, TS ...>;
        using RxLink = RxLink<T, FN, TS ...>;
        using RxLinks = std::unordered_map<const Rx *, RxLink>;

        static auto & instance();

        void connect(Rx & rx,
                     FN fn,
                     const Var<TS> & ... vars) {
            rxLinks[&rx] = RxLink(tuple::MakeTuple(&vars ...));
            react::connect(rx, vars ...);
        }

        void disconnect(const Rx & rx) {
            rxLinks.erase(&rx);
        }

        T compute(const Rx & rx) {
            // TODO implement this
            return T{};
        }

    private:
        RxDispatcher() = default;

        RxLinks rxLinks;
    };

    template <class T, class FN, class ... TS>
    auto & RxDispatcher<T, FN, TS ...>::instance() {
        static RxDispatcher dispatcher;
        return dispatcher;
    }

}

#endif // RXDISPATCHER_HPP
