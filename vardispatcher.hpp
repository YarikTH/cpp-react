#pragma once

#ifndef VARDISPATCHER_HPP
#define VARDISPATCHER_HPP

namespace react {

    template <class T>
    class Var;

    template <class T>
    class VarDispatcher {
    public:
        static auto & instance();

        void connect(const Var<T> & var) {
            // TODO implement this
        }

        void disconnect(const Var<T> & var) {
            // TODO implement this
        }

        void notifyChange(const Var<T> & var) {
            // TODO implement this
        }

    private:
        VarDispatcher() = default;
    };

    template <class T>
    auto & VarDispatcher<T>::instance() {
        static VarDispatcher dispatcher;
        return dispatcher;
    }

}

#endif // VARDISPATCHER_HPP
