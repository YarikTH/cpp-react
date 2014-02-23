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
    void connect(VarListener &, const Link<T> &);

    template <class T, class TT, class ... TS>
    void connect(VarListener &, const Link<T, TT, TS ...> &);

    template <class T>
    const auto & value(const Var<T> *, const VarListener &);

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
            react::connect(rx, link);
        }

        void disconnect(const RxT & rx) {
            links.erase(&rx);
        }

        T compute(const RxT & rx, FN fn) const {
            return compute(rx, fn, AllIndices());
        }

    private:
        RxDispatcher() = default;

        template <unsigned int INDEX>
        const auto & value(const RxT & rx, const Tuple & tp) const {
            return react::value(Accessor<INDEX>::Get(tp), rx);
        }

        template <unsigned int ... INDICES>
        T compute(const RxT & rx, FN fn, const Indices<INDICES ...> &) const {
            auto & link = query(links, &rx);
            return fn(value<INDICES>(rx, link.getVars()) ...);
        }

        Links links;
    };

}

#endif // RXDISPATCHER_HPP
