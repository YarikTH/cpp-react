#pragma once

#ifndef RXDISPATCHER_HPP
#define RXDISPATCHER_HPP

#include "vardispatcher.hpp"
#include "link.hpp"
#include <unordered_map>

namespace react {

    template <class T>
    class Var;

    template <class ... TS>
    class Link;

    template <class T, class FN, class ... TS>
    class Rx;

    template <class T, class ... TS>
    void connect(VarListener & listener,
                 const Var<T> & var,
                 const Var<TS> & ... vars);

    template <class T>
    void connect(VarListener & listener, const Link<T> & link);

    template <class T, class TT, class ... TS>
    void connect(VarListener & listener, const Link<T, TT, TS ...> & link);

    template <class T>
    const auto & value(const Var<T> * var);

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
            links[&rx] = link;
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
        const auto & value(const Tuple & tp) const {
            return react::value(Accessor<INDEX>::Get(tp));
        }

        template <unsigned int ... INDICES>
        T compute(const RxT & rx, FN fn, const Indices<INDICES ...> &) const {
            auto it = links.find(&rx);

            if (it != links.end()) {
                return fn(value<INDICES>(it->second.getVars())...);
            }
            else {
                return T{};
            }
        }

        Links links;
    };

}

#endif // RXDISPATCHER_HPP
