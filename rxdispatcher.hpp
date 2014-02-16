#pragma once

#ifndef RXDISPATCHER_HPP
#define RXDISPATCHER_HPP

namespace react {

    template <class T>
    class Var;

    template <class T, class FN, class ... TS>
    class Rx;

    template <class T, class FN, class ... TS>
    class RxDispatcher {
    public:
        static auto & instance();

        void connect(const Rx<T, FN, TS ...> & rx,
                     FN fn,
                     const Var<TS> & ... vars) {
            // TODO implement this
        }

        void disconnect(const Rx<T, FN, TS ...> & rx) {
            // TODO implement this
        }

        T compute(const Rx<T, FN, TS ...> & rx) {
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
