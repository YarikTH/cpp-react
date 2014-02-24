#pragma once

#ifndef RXDISPATCHER_HPP
#define RXDISPATCHER_HPP

#include "vardispatcher.hpp"
#include "link.hpp"
#include "exceptions.hpp"
#include <unordered_map>

namespace react {

    template <class T>
    class Var;

    template <class ... TS>
    class Link;

    template <class T, class FN, class ... TS>
    class Rx;

    template <class T>
    class VarDispatcher;

    template <class T, class FN, class ... TS>
    class RxDispatcher {
    public:
        using RxT = Rx<T, FN, TS ...>;
        using LinkT = Link<TS ...>;
        using Links = std::unordered_map<const RxT *, LinkT>;
        using Tuple = typename LinkT::Tuple;
        using AllIndices = typename Tuple::AllIndices;
        template <unsigned int ... INDICES>
        using Indices = tuple::Indices<INDICES ...>;
        template <unsigned int INDEX>
        using Accessor = tuple::Accessor<INDEX, const Var<TS> * ...>;

        static auto & instance() {
            static RxDispatcher dispatcher;
            return dispatcher;
        }

        void connect(RxT & rx, const LinkT & link) {
            set(links, &rx, link);
            connectListener(rx, link);
        }

        void disconnect(RxT & rx) {
            disconnectListener(rx, query(links, &rx));
            erase(links, &rx);
        }

        T compute(const RxT & rx, FN fn) const {
            return compute(rx, fn, AllIndices());
        }

    private:
        RxDispatcher() = default;

        template <class U>
        const auto & value(const RxT & rx, const Var<U> * v) const {
            return VarDispatcher<U>::instance().value(v, rx);
        }

        template <unsigned int INDEX>
        const auto & var(const RxT & rx, const LinkT & l) const {
            return Accessor<INDEX>::Get(l.getVars());
        }

        template <unsigned int ... INDICES>
        T compute(const RxT & rx, FN fn, const Indices<INDICES ...> &) const {
            auto & l = query(links, &rx);
            return fn(value(rx, var<INDICES>(rx, l)) ...);
        }

        template <class U>
        void connectListener(RxT & rx, const Link<U> & l) {
            const auto & var = l.getVars().GetFirst();
            VarDispatcher<U>::instance().connect(var, rx);
        }

        template <class U, class UU, class ... US>
        void connectListener(RxT & rx, const Link<U, UU, US ...> & l) {
            const auto & var = l.getVars().GetFirst();
            VarDispatcher<U>::instance().connect(var, rx);
            connectListener(rx, Link<UU, US ...>(*l.getVars().Next()));
        }

        template <class U>
        void disconnectListener(RxT & rx, const Link<U> & l) {
            const auto & var = l.getVars().GetFirst();
            VarDispatcher<U>::instance().disconnect(var, rx);
        }

        template <class U, class UU, class ... US>
        void disconnectListener(RxT & rx, const Link<U, UU, US ...> & l) {
            const auto & var = l.getVars().GetFirst();
            VarDispatcher<U>::instance().disconnect(var, rx);
            disconnectListener(rx, Link<UU, US ...>(*l.getVars().Next()));
        }

        Links links;
    };

}

#endif // RXDISPATCHER_HPP
