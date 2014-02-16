#pragma once

#ifndef RX_HPP
#define RX_HPP

#include <utility>
#include "var.hpp"
#include "varlistener.hpp"
#include "dispatcher.hpp"

namespace react {

    template <class T>
    class Var;

    class Dispatcher;

    template <class T, class FN, class ... TS>
    class Rx : public Var<T>, public VarListener {
    public:
        Rx(FN fn, const Var<TS> & ... sources) {
            Dispatcher::instance().connect(*this, fn, sources ...);
        }
        virtual ~Rx() {
            Dispatcher::instance().disconnect(*this);
        }

        virtual void update() override {
            Var<T>::operator=(Dispatcher::instance().compute(*this));
        }

    private:
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
