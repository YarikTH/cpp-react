/*

  react LGPL Source Code
  Copyright (C) 2014 Edward Knyshov

  This file is part of the react LGPL Source Code (react Source Code).

  react Source Code is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  react Source Code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with react Source Code. If not, see <http://www.gnu.org/licenses/>

*/

#pragma once

#ifndef VAR_HPP
#define VAR_HPP

#include <utility>
#include "vardispatcher.hpp"
#include "rx.hpp"
#include "rxrelaxed.hpp"

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

        auto & operator=(const T& newValue) {
            value = newValue;
            dispatcher().notifyChange(*this);
            return *this;
        }

        auto & operator=(T&& newValue) {
            value = std::move(newValue);
            dispatcher().notifyChange(*this);
            return *this;
        }

        template <class U>
        auto & operator=(U && newValue) {
            value = std::forward<U>(newValue);
            dispatcher().notifyChange(*this);
            return *this;
        }

        operator const T&() const {
            return value;
        }

        const auto & operator()() const {
            return value;
        }

        const auto& getValue() const {
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

        template <class FN>
        auto rxRelaxed(FN && f) const {
            using RxType = RxRelaxed<decltype(f(value))>;
            return RxType{std::forward<FN>(f), link(*this)};
        }

        auto rxRelaxed() const {
            return rxRelaxed([] (auto a) {
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
