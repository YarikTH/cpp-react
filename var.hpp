#pragma once

#ifndef VAR_HPP
#define VAR_HPP

#include <utility>
#include "vardispatcher.hpp"

namespace react {

    template <class T>
    class Var {
    public:
        static auto & dispatcher() {
            return VarDispatcher<T>::instance();
        }

        Var() {
            dispatcher().connect(*this);
        }

        Var(const T & newValue):
            value(newValue) {
            dispatcher().connect(*this);
        }

        Var(T && newValue):
            value(std::move(newValue)) {
            dispatcher().connect(*this);
        }

        ~Var() {
            dispatcher().disconnect(*this);
        }

        template <class U>
        auto & operator=(U && newValue) {
            value = std::forward<U>(newValue);
            dispatcher().notifyChange(*this);
            return *this;
        }

        const auto & operator()() const {
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
    inline auto var(T && value) {
        return Var<T>(std::forward<T>(value));
    }

} // namespace react

#endif // VAR_HPP
