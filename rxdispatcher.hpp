/*

  react LGPL Source Code
  Copyright (C) 2014 Edward Knyshov

  This file is part of the react LGPL Source Code (react Source Code).

  react Source Code is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  react Source Code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with react Source Code. If not, see <http://www.gnu.org/licenses/>

*/

#pragma once

#ifndef RXDISPATCHER_HPP
#define RXDISPATCHER_HPP

#include "vardispatcher.hpp"
#include "link.hpp"
#include "exceptions.hpp"
#include <unordered_map>
#include <functional>

namespace react {

    template <class T>
    class Var;

    template <class ... TS>
    class Link;

    template <class T, class ... TS>
    class Rx;

    template <class T>
    class VarDispatcher;

    template <class T, class ... TS>
    class RxDispatcher {
    public:
        using RxT = Rx<T, TS ...>;
        using Fn = std::function<T(const TS & ...)>;
        using LinkT = Link<TS ...>;

        using RxesLinks = std::unordered_map<const RxT *, LinkT>;
        using RxesFns = std::unordered_map<const RxT *, Fn>;

        template <unsigned int INDEX>
        using Accessor = tuple::Accessor<INDEX, const Var<TS> * ...>;
        template <unsigned int ... INDICES>
        using Indices = tuple::Indices<INDICES ...>;
        using AllIndices = typename LinkT::Tuple::AllIndices;

        static auto & instance() {
            static RxDispatcher dispatcher;
            return dispatcher;
        }

        template <class FN, class LINK>
        void connect(RxT & rx, FN && f, LINK && l) {
            set(rxesLinks, &rx, std::forward<LINK>(l));
            set(rxesFns, &rx, std::forward<FN>(f));
            connectRxToLink(rx, l);
        }

        void disconnect(RxT & rx) {
            disconnectRxFromLink(rx, query(rxesLinks, &rx));
            erase(rxesFns, &rx);
            erase(rxesLinks, &rx);
        }

        T compute(const RxT & rx) const {
            return compute(rx, AllIndices{});
        }

        void updateLink(RxT & rx) {
            updateLink(rx, AllIndices{});
        }

        bool connected(RxT & rx) {
            return rxesLinks.find(&rx) != rxesLinks.end() &&
                rxesFns.find(&rx) != rxesFns.end();
        }

        template <class FN>
        void setFn(RxT & rx, FN && fn) {
            query(rxesFns, &rx);
            rxesFns[&rx] = std::forward<FN>(fn);
        }

    private:
        RxDispatcher() = default;

        template <unsigned int INDEX>
        const auto & var(const LinkT & l) const {
            return Accessor<INDEX>::Get(l.getVars());
        }

        // computing

        template <class U>
        const auto & varValue(const RxT & rx, const Var<U> * v) const {
            return VarDispatcher<U>::instance().value(v, rx);
        }

        template <unsigned int ... INDICES>
        T compute(const RxT & rx, const Indices<INDICES ...> &) const {
            auto & l = query(rxesLinks, &rx);
            auto & f = query(rxesFns, &rx);
            return f(varValue(rx, var<INDICES>(l)) ...);
        }

        // link updating

        template <class U>
        const Var<U> & reincarnatedVar(const Var<U> * v, RxT & rx) {
            return VarDispatcher<U>::instance().reincarnatedVar(v, rx);
        }

        template <unsigned int ... INDICES>
        void updateLink(RxT & rx, const Indices<INDICES ...> &) {
            auto & l = query(rxesLinks, &rx);
            l = link(reincarnatedVar(var<INDICES>(l), rx) ...);
        }

        // connecting

        template <class U>
        void connectRxToLink(RxT & rx, const Link<U> & l) {
            const auto & var = l.getVars().GetFirst();
            VarDispatcher<U>::instance().connect(var, rx);
        }

        template <class U, class UU, class ... US>
        void connectRxToLink(RxT & rx, const Link<U, UU, US ...> & l) {
            const auto & var = l.getVars().GetFirst();
            VarDispatcher<U>::instance().connect(var, rx);
            connectRxToLink(rx, Link<UU, US ...>(*l.getVars().Next()));
        }

        // diconnecting

        template <class U>
        void disconnectRxFromLink(RxT & rx, const Link<U> & l) {
            const auto & var = l.getVars().GetFirst();
            VarDispatcher<U>::instance().disconnect(var, rx);
        }

        template <class U, class UU, class ... US>
        void disconnectRxFromLink(RxT & rx, const Link<U, UU, US ...> & l) {
            const auto & var = l.getVars().GetFirst();
            VarDispatcher<U>::instance().disconnect(var, rx);
            disconnectRxFromLink(rx, Link<UU, US ...>(*l.getVars().Next()));
        }

        RxesLinks rxesLinks;
        RxesFns rxesFns;
    };

}

#endif // RXDISPATCHER_HPP
