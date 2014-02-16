#pragma once

#ifndef RXDISPATCHER_HPP
#define RXDISPATCHER_HPP

namespace react {

    template <class T>
    class Var;

    template <class T, class FN, class ... TS>
    class Rx;

    class RxDispatcher {
    public:
        static auto & instance();

        template <class T, class FN, class ... TS>
        void connect(const Rx<T, FN, TS ...> & rx,
                     FN fn,
                     const Var<TS> & ... sources) {
            // TODO implement this
        }

        template <class T, class FN, class ... TS>
        void disconnect(const Rx<T, FN, TS ...> & rx) {
            // TODO implement this
        }

        template <class T, class FN, class ... TS>
        T compute(const Rx<T, FN, TS ...> & rx) {
            // TODO implement this
            return T{};
        }

    private:
        RxDispatcher() = default;
    };

    auto & RxDispatcher::instance() {
        static RxDispatcher dispatcher;
        return dispatcher;
    }

}

#endif // RXDISPATCHER_HPP
