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
