#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <unordered_map>
#include "var.hpp"

namespace react {

    template <class T>
    class Var;

    template <class T>
    class Dispatcher {
    public:
        using StoredType = T;

        static auto & instance();

        void connect(const Var<StoredType> & source) {
            // TODO implement this
        }
        template <class T2, class CALLABLE>
        void connect(const Var<StoredType> & source,
                     const Var<T2> & dest,
                     CALLABLE function) {
            // TODO implement this
        }
        void disconnect(const Var<StoredType> & source) {
            // TODO implement this
        }
        void notifyChange(const Var<StoredType> & source) {
            // TODO implement this
        }

    private:
        Dispatcher() = default;
    };

    template <class T>
    auto & Dispatcher<T>::instance() {
        static Dispatcher<StoredType> dispatcher;
        return dispatcher;
    }

}

#endif // DISPATCHER_HPP
