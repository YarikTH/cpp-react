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

        Rx() = delete;
        Rx(const Rx &) = delete;

        Rx(Rx && newRx) {
            // TODO implement reincarnation
        }

        template <class FN, class LINK>
        Rx(FN && f, LINK && l) {
            dispatcher().connect(*this,
                                 std::forward<FN>(f),
                                 std::forward<LINK>(l));
            updateValue();
        }

        virtual ~Rx() {
            dispatcher().disconnect(*this);
        }

        template <class U>
        auto & operator=(U && newValue) {
            Var<T>::operator=(std::forward<U>(newValue));
            return *this;
        }

        virtual void updateValue() override {
            *this = dispatcher().compute(*this);
        }

        virtual void updateLink() override {
            dispatcher().updateLink(*this);
        }
    };

} // namespace react

#endif // RX_HPP
