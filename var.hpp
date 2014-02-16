#pragma once

#ifndef VAR_HPP
#define VAR_HPP

#include <utility>
#include "vardispatcher.hpp"

namespace react {

    template <class T>
    class Var {
    public:
        using VarDispatcher = VarDispatcher<T>;

        Var() {
            VarDispatcher::instance().connect(*this);
        }
        Var(const T & newValue):
            value(newValue) {
            VarDispatcher::instance().connect(*this);
        }
        Var(T && newValue):
            // value(std::forward(newValue)) {
            value(std::move(newValue)) {
            VarDispatcher::instance().connect(*this);
        }
        ~Var() {
            VarDispatcher::instance().disconnect(*this);
        }

        auto & operator= (const T & newValue) {
            value = newValue;
            VarDispatcher::instance().notifyChange(*this);
            return *this;
        }
        auto & operator= (T && newValue) {
            value = std::move(newValue);
            VarDispatcher::instance().notifyChange(*this);
            return *this;
        }

        const auto & getValue() const {
            return value;
        }

        operator const T & () {
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

        T value = T{};
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

} // namespace react

#endif // VAR_HPP
