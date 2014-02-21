#pragma once

#ifndef VAR_HPP
#define VAR_HPP

#include <utility>
#include "vardispatcher.hpp"

namespace react {

    template <class T>
    class Var {
    public:
        using VarDispatcherT = VarDispatcher<T>;

        Var() {
            VarDispatcherT::instance().connect(*this);
        }

        Var(const T & newValue):
            value(newValue) {
            VarDispatcherT::instance().connect(*this);
        }

        Var(T && newValue):
            value(std::move(newValue)) {
            VarDispatcherT::instance().connect(*this);
        }

        ~Var() {
            VarDispatcherT::instance().disconnect(*this);
        }

        template <class U>
        auto & operator=(U && newValue) {
            value = std::forward<U>(newValue);
            VarDispatcherT::instance().notifyChange(*this);
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
    inline auto makeVar(T && value) {
        return Var<T>(std::forward<T>(value));
    }

} // namespace react

#endif // VAR_HPP
