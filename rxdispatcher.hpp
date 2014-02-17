#pragma once

#ifndef RXDISPATCHER_HPP
#define RXDISPATCHER_HPP

#include "vardispatcher.hpp"

namespace react {

    template <class T>
    class Var;

    template <class T, class FN, class ... TS>
    class Rx;

    template <class T, class FN, class ... TS>
    class RxDispatcher {
    public:
        using Rx = Rx<T, FN, TS ...>;

        static auto & instance();

        void connect(Rx & rx,
                     FN fn,
                     const Var<TS> & ... vars) {
            react::connect(rx, vars ...);
        }

        void disconnect(const Rx & rx) {
            // TODO implement this
        }

        T compute(const Rx & rx) {
            // TODO implement this
            return T{};
        }

    private:
        RxDispatcher() = default;
    };

    template <class T, class FN, class ... TS>
    auto & RxDispatcher<T, FN, TS ...>::instance() {
        static RxDispatcher dispatcher;
        return dispatcher;
    }

}

#endif // RXDISPATCHER_HPP
