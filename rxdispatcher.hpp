#pragma once

#ifndef RXDISPATCHER_HPP
#define RXDISPATCHER_HPP

#include "vardispatcher.hpp"
#include "rxlink.hpp"
#include <unordered_map>

namespace react {

    template <class T>
    class Var;

    template <class T, class FN, class ... TS>
    class Rx;

    template <class T, class FN, class ... TS>
    class RxDispatcher {
    public:
        using Rx = Rx<T, FN, TS ...>;
        using RxLink = RxLink<T, FN, TS ...>;
        using RxLinks = std::unordered_map<const Rx *, RxLink>;
        using Tuple = typename RxLink::Tuple;
        using AllIndices = typename Tuple::AllIndices;
        template <unsigned int ... INDICES>
        using Indices = tuple::Indices<INDICES ...>;
        template <unsigned int INDEX>
        using Accessor = tuple::Accessor<INDEX, const Var<TS> * ...>;

        static auto & instance() {
            static RxDispatcher dispatcher;
            return dispatcher;
        }

        void connect(Rx & rx,
                     const Var<TS> & ... vars) {
            rxLinks[&rx] = RxLink(Tuple(&vars ...));
            react::connect(rx, vars ...);
        }

        void disconnect(const Rx & rx) {
            rxLinks.erase(&rx);
        }

        T compute(const Rx & rx, FN fn) const {
            return compute(rx, fn, AllIndices());
        }

    private:
        RxDispatcher() = default;

        template <unsigned int INDEX>
        const auto & value(const Tuple & tp) const {
            return react::value(Accessor<INDEX>::Get(tp));
        }

        template <unsigned int ... INDICES>
        T compute(const Rx & rx, FN fn, const Indices<INDICES ...> &) const {
            auto it = rxLinks.find(&rx);

            if (it != rxLinks.end()) {
                return fn(value<INDICES>(it->second.vars)...);
            }
            else {
                return T{};
            }
        }

        RxLinks rxLinks;
    };

}

#endif // RXDISPATCHER_HPP
