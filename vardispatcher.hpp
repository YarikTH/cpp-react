#pragma once

#ifndef VARDISPATCHER_HPP
#define VARDISPATCHER_HPP

namespace react {

    template <class T>
    class Var;

    template <class T, class FN, class ... TS>
    class Rx;

    class VarDispatcher {
    public:
        static auto & instance();

        template <class T>
        void connect(const Var<T> & var) {
            // TODO implement this
        }

        template <class T>
        void disconnect(const Var<T> & var) {
            // TODO implement this
        }

        template <class T>
        void notifyChange(const Var<T> & src) {
            // TODO implement this
        }

    private:
        VarDispatcher() = default;
    };

    auto & VarDispatcher::instance() {
        static VarDispatcher dispatcher;
        return dispatcher;
    }

}

#endif // VARDISPATCHER_HPP
