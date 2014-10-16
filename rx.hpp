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

#ifndef RX_HPP
#define RX_HPP

#include <utility>
#include "var.hpp"
#include "varlistener.hpp"
#include "rxdispatcher.hpp"

namespace react {

    template <class T>
    class Var;

    template <class ... TS>
    class Link;

    template <class T, class ... TS>
    class RxDispatcher;

    template <class T, class ... TS>
    class Rx : public Var<T>, public VarListener {
    public:
        static auto & dispatcher() {
            return RxDispatcher<T, TS ...>::instance();
        }

        Rx() = default;
        Rx(const Rx &) = delete;

        Rx(Rx && newRx) {
            // TODO implement reincarnation
        }

        template <class FN, class LINK>
        Rx(FN && f, LINK && l) {
            reconnect(std::forward<FN>(f), std::forward<LINK>(l));
        }

        virtual ~Rx() {
            if (dispatcher().connected(*this))
                dispatcher().disconnect(*this);
        }

        template <class U>
        auto & operator=(U && newValue) {
            Var<T>::operator=(std::forward<U>(newValue));
            return *this;
        }

        virtual void updateValue() override {
            if (dispatcher().connected(*this))
                *this = dispatcher().compute(*this);
        }

        virtual void updateLink() override {
            if (dispatcher().connected(*this))
                dispatcher().updateLink(*this);
        }

        template <class FN>
        void setFn(FN && fn) {
            if (!dispatcher().connected(*this))
                return;

            dispatcher().setFn(*this, std::forward<FN>(fn));
            *this = dispatcher().compute(*this);
        }

        template <class FN, class LINK>
        void reconnect(FN && f, LINK && l) {
            if (dispatcher().connected(*this))
                dispatcher().disconnect(*this);

            dispatcher().connect(*this,
                                 std::forward<FN>(f),
                                 std::forward<LINK>(l));
            *this = dispatcher().compute(*this);
        }
    };

} // namespace react

#endif // RX_HPP
