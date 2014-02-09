#ifndef VAR_HPP
#define VAR_HPP

#include <utility>
#include "dispatcher.hpp"

namespace react {

    template <class T>
    class Var {
    public:
        using StoredType = T;

        Var() {
            Dispatcher<StoredType>::instance().connect(*this);
        }
        Var(const StoredType & newValue):
            value(newValue) {
            Dispatcher<StoredType>::instance().connect(*this);
        }
        Var(StoredType && newValue):
            value(std::move(newValue)) {
            Dispatcher<StoredType>::instance().connect(*this);
        }
        ~Var() {
            Dispatcher<StoredType>::instance().disconnect(*this);
        }

        Var & operator= (const StoredType & newValue) {
            value = newValue;
            Dispatcher<StoredType>::instance().notifyChange(*this);
            return *this;
        }
        Var & operator= (StoredType && newValue) {
            value = std::move(newValue);
            Dispatcher<StoredType>::instance().notifyChange(*this);
            return *this;
        }

        const StoredType & getValue() const {
            return value;
        }

        operator const StoredType & () {
            return value;
        }

    private:
        StoredType value = StoredType{};
    };

    template <class T>
    inline Var<T> makeVar(const T & value) {
        return Var<T>(value);
    }

    template <class T>
    inline Var<T> makeVar(T && value) {
        return Var<T>(std::move(value));
    }

} // namespace react

#endif // VAR_HPP
