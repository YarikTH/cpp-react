#ifndef RXDISPATCHERACCESSOR_HPP
#define RXDISPATCHERACCESSOR_HPP

#include "rxdispatcher.hpp"
#include "link.hpp"
#include "rx.hpp"
#include "exceptions.hpp"
#include <unordered_map>
#include <functional>
#include <utility>

namespace react {

    template <class T>
    class RxDispatcherAccessorNode;

    template <class T, class ... U>
    class RxDispatcherAccessorNodeImpl;

    template <class T>
    class RxDispatcherAccessor {
    public:
        static auto & instance() {
            static RxDispatcherAccessor res;
            return res;
        }

        template <class ... U>
        static auto & dispatcher() {
            return RxDispatcher<T, U ...>::instance();
        }

        template <class FN, class ... U>
        void connect(VarListener & rx, FN && f, const Link<U ...> & l) {
            set(rxDispatchers, &rx, &RxDispatcherAccessorNodeImpl<T, U ...>::instance());
            dispatcher<U ...>().connect(static_cast<Rx<T, U ...> &>(rx),
                                        std::forward<FN>(f),
                                        l);
        }

        template <class FN, class ... U>
        void connect(VarListener & rx, FN && f, Link<U ...> && l) {
            set(rxDispatchers, &rx, &RxDispatcherAccessorNodeImpl<T, U ...>::instance());
            dispatcher<U ...>().connect(static_cast<Rx<T, U ...> &>(rx),
                                        std::forward<FN>(f),
                                        std::move(l));
        }

        void disconnect(VarListener & l) {
            query(rxDispatchers, &l)->disconnect(l);
            erase(rxDispatchers, &l);
        }

        T compute(VarListener & l) const {
            return query(rxDispatchers, &l)->compute(l);
        }

        void updateLink(VarListener & l) {
            query(rxDispatchers, &l)->updateLink(l);
        }

        bool connected(VarListener & l) {
            return rxDispatchers.find(&l) != rxDispatchers.end();
        }

        template <class ... U>
        void setFn(VarListener & rx, const std::function<T(U ...)> & fn) {
            dispatcher<U ...>().setFn(static_cast<Rx<T, U ...> &>(rx),
                                      fn);
        }

        template <class ... U>
        void setFn(VarListener & rx, std::function<T(U ...)> && fn) {
            dispatcher<U ...>().setFn(static_cast<Rx<T, U ...> &>(rx),
                                      std::move(fn));
        }

    private:
        RxDispatcherAccessor() = default;

        std::unordered_map<VarListener *, RxDispatcherAccessorNode<T> *> rxDispatchers;
    };

    // template <class T>
    // std::unordered_map<Rx<T> *, RxDispatcherAccessorNode<T> *> RxDispatcherAccessor::rxDispatchers;

    template <class T>
    class RxDispatcherAccessorNode {
    public:
        virtual void disconnect(VarListener & l) const = 0;
        virtual T compute(VarListener & l) const = 0;
        virtual void updateLink(VarListener & l) const = 0;
    };

    template <class T, class ... U>
    class RxDispatcherAccessorNodeImpl : public RxDispatcherAccessorNode<T> {
    public:
        static auto & instance() {
            static RxDispatcherAccessorNodeImpl res;
            return res;
        }

        static auto & dispatcher() {
            return RxDispatcher<T, U ...>::instance();
        }

        virtual void disconnect(VarListener & l) const override {
            dispatcher().disconnect(static_cast<Rx<T, U ...> &>(l));
        }

        virtual T compute(VarListener & l) const override {
            return dispatcher().compute(static_cast<Rx<T, U ...> &>(l));
        }

        virtual void updateLink(VarListener & l) const override {
            dispatcher().updateLink(static_cast<Rx<T, U ...> &>(l));
        }

    private:
        RxDispatcherAccessorNodeImpl() = default;
    };

}

#endif // RXDISPATCHERACCESSOR_HPP
