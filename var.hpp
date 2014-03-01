#pragma once

#ifndef VAR_HPP
#define VAR_HPP

#include <utility>
#include "vardispatcher.hpp"
#include "rx.hpp"

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

        Var(const Var &) = delete;

        Var(Var && newVar):
            Var(std::move(newVar.value)) {
            dispatcher().reincarnate(newVar, *this);
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

        template <class FN>
        auto rx(FN && f) const {
            using RxType = Rx<decltype(f(value)), T>;
            return RxType(std::forward<FN>(f), link(*this));
        }

        auto rx() const {
            return rx([] (auto a) {
                    return a;
                });
        }

    private:
        T value = T{};
    };

    template <class T>
    inline auto var(T && value) {
        return Var<T>(std::forward<T>(value));
    }

} // namespace react

#endif // VAR_HPP
