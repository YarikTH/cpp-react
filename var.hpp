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
        template <class T2, class CALLABLE>
        Var(const Var<T2> & source, CALLABLE newFunction) {
            Dispatcher<T2>::instance().connect(source,
                                               *this,
                                               newFunction);
        }
        ~Var() {
            Dispatcher<StoredType>::instance().disconnect(*this);
        }

        auto & operator= (const StoredType & newValue) {
            value = newValue;
            Dispatcher<StoredType>::instance().notifyChange(*this);
            return *this;
        }
        auto & operator= (StoredType && newValue) {
            value = std::move(newValue);
            Dispatcher<StoredType>::instance().notifyChange(*this);
            return *this;
        }

        const auto & getValue() const {
            return value;
        }

        operator const StoredType & () {
            return value;
        }

        auto getId() const {
            return id;
        }

    private:
        static auto genId() {
            // TODO: use real generation
            static auto idPending = 0;
            return idPending++;
        }

        StoredType value = StoredType{};
        int id = genId();
    };

    template <class T>
    inline auto makeVar(const T & value) {
        return Var<T>(value);
    }

    template <class T>
    inline auto makeVar(T && value) {
        return Var<T>(std::move(value));
    }

    template <class T, class CALLABLE>
    inline auto makeVar(const Var<T> & source, CALLABLE function) {
        using Result = Var<decltype(function(source.getValue()))>;
        return Result(source, function);
    }

} // namespace react

#endif // VAR_HPP
