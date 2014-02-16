#pragma once

#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

namespace react {

    template <class T>
    class Var;

    template <class T, class FN, class ... TS>
    class Rx;

    class Dispatcher {
    public:
        static auto & instance();

        template <class T>
        void connect(const Var<T> & var) {
            // TODO implement this
        }

        template <class T, class FN, class ... TS>
        void connect(const Rx<T, FN, TS ...> & rx,
                     FN fn,
                     const Var<TS> & ... sources) {
            // TODO implement this
        }

        template <class T>
        void disconnect(const Var<T> & var) {
            // TODO implement this
        }

        template <class T, class FN, class ... TS>
        void disconnect(const Rx<T, FN, TS ...> & rx) {
            // TODO implement this
        }

        template <class T>
        void notifyChange(const Var<T> & src) {
            // TODO implement this
        }

        template <class T, class FN, class ... TS>
        T compute(const Rx<T, FN, TS ...> & rx) {
            // TODO implement this
            return T{};
        }

    private:
        Dispatcher() = default;
    };

    auto & Dispatcher::instance() {
        static Dispatcher dispatcher;
        return dispatcher;
    }

}

#endif // DISPATCHER_HPP
