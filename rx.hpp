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

    template <class T, class FN, class ... TS>
    class RxDispatcher;

    template <class T, class FN, class ... TS>
    class Rx : public Var<T>, public VarListener {
    public:
        auto & dispatcher() {
            return RxDispatcher<T, FN, TS ...>::instance();
        }

        Rx(FN newFn, const Var<TS> & ... sources):
            fn(newFn) {
            dispatcher().connect(*this, sources ...);
            update();
        }

        virtual ~Rx() {
            dispatcher().disconnect(*this);
        }

        virtual void update() override {
            Var<T>::operator=(dispatcher().compute(*this, fn));
        }

    private:
        FN fn;
    };

    template <class FN, class ... TS>
    inline auto makeRx(FN fn, const Var<TS> & ... sources) {
        using T = decltype(fn(sources.getValue() ...));
        using Result = Rx<T, FN, TS ...>;
        return Result(fn, sources ...);
    }

    template <class FN, class TS>
    inline auto makeRx(const Var<TS> & var, FN fn) {
        using T = decltype(fn(var.getValue()));
        using Result = Rx<T, FN, T>;
        return Result(fn, var);
    }

} // namespace react

#endif // RX_HPP
