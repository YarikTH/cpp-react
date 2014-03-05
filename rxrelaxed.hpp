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

        RxRelaxed() = delete;
        RxRelaxed(const RxRelaxed &) = delete;

        RxRelaxed(RxRelaxed && newRxRelaxed) {
            // TODO implement reincarnation
        }

        template <class FN, class ... U>
        RxRelaxed(FN && f, const Link<U ...> & l) {
            dispatcher().connect(*this,
                                 std::forward<FN>(f),
                                 l);
            updateValue();
        }

        virtual ~RxRelaxed() {
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

#endif // RXRELAXED_HPP
