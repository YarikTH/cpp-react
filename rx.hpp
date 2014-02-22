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

    template <class T, class FN, class ... TS>
    class RxDispatcher;

    template <class T, class FN, class ... TS>
    class Rx : public Var<T>, public VarListener {
    public:
        static auto & dispatcher() {
            return RxDispatcher<T, FN, TS ...>::instance();
        }

        Rx(FN newFn, const Link<TS ...> & link):
            fn(newFn) {
            dispatcher().connect(*this, link);
            update();
        }

        virtual ~Rx() {
            dispatcher().disconnect(*this);
        }

        template <class U>
        auto & operator=(U && newValue) {
            Var<T>::operator=(std::forward<U>(newValue));
            return *this;
        }

        virtual void update() override {
            *this = dispatcher().compute(*this, fn);
        }

    private:
        FN fn;
    };

} // namespace react

#endif // RX_HPP
