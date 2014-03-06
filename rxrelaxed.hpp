#pragma once

#ifndef RXRELAXED_HPP
#define RXRELAXED_HPP

#include <utility>
#include "var.hpp"
#include "varlistener.hpp"
#include "rxdispatcheraccessor.hpp"

namespace react {

    template <class T>
    class Var;

    template <class ... TS>
    class Link;

    template <class T>
    class RxRelaxed : public Var<T>, public VarListener {
    public:
        static auto & dispatcher() {
            return RxDispatcherAccessor<T>::instance();
        }

        RxRelaxed() = default;
        RxRelaxed(const RxRelaxed &) = delete;

        RxRelaxed(RxRelaxed && newRxRelaxed) {
            // TODO implement reincarnation
        }

        template <class FN, class ... U>
        RxRelaxed(FN && f, const Link<U ...> & l) {
            reconnect(std::forward<FN>(f), l);
        }

        template <class FN, class ... U>
        RxRelaxed(FN && f, Link<U ...> && l) {
            reconnect(std::forward<FN>(f), std::move(l));
        }

        virtual ~RxRelaxed() {
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

        template <class FN, class ... U>
        void reconnect(FN && f, const Link<U ...> & l) {
            if (dispatcher().connected(*this))
                dispatcher().disconnect(*this);

            dispatcher().connect(*this, std::forward<FN>(f), l);
            *this = dispatcher().compute(*this);
        }

        template <class FN, class ... U>
        void reconnect(FN && f, Link<U ...> && l) {
            if (dispatcher().connected(*this))
                dispatcher().disconnect(*this);

            dispatcher().connect(*this,
                                 std::forward<FN>(f),
                                 std::move(l));
            updateValue();
            *this = dispatcher().compute(*this);
        }
    };

} // namespace react

#endif // RXRELAXED_HPP
