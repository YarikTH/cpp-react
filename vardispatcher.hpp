#pragma once

#ifndef VARDISPATCHER_HPP
#define VARDISPATCHER_HPP

#include <unordered_set>
#include <unordered_map>
#include "varlistener.hpp"
#include "link.hpp"
#include "exceptions.hpp"

namespace react {

    template <class T>
    class Var;

    template <class T>
    class VarDispatcher {
    public:
        using VarT = Var<T>;
        using Listeners = std::unordered_set<VarListener *>;
        using VarsListeners = std::unordered_map<const VarT *, Listeners>;
        using VarsValues = std::unordered_map<const VarT *, T>;
        using ListenersVarsValues = std::unordered_map<const VarListener *, VarsValues>;

        static auto & instance() {
            static VarDispatcher dispatcher;
            return dispatcher;
        }

        void connect(const VarT & v) {
            varsListeners[&v];
        }

        void connect(const VarT & v, VarListener & l) {
            query(varsListeners, &v).insert(&l);
        }

        void disconnect(const VarT & v) {
            auto it = varsListeners.find(&v);

            for (auto & l : it->second) {
                destroyedVarsValues[l][&v] = v();
            }

            varsListeners.erase(it);
        }

        void disconnect(const VarT & v, VarListener & l) {
            query(varsListeners, &v).erase(&l);
        }

        void notifyChange(const VarT & v) {
            for (auto & l : query(varsListeners, &v)) l->update();
        }

        const T & value(const VarT * v, const VarListener & l) {
            auto varsValues = destroyedVarsValues.find(&l);

            if (varsValues != destroyedVarsValues.end()) {
                auto val = varsValues->second.find(v);

                if (val != varsValues->second.end()) {
                    return val->second;
                }
            }

            query(varsListeners, v);

            return (*v)();
        }

    private:
        VarDispatcher() = default;

        VarsListeners varsListeners;
        ListenersVarsValues destroyedVarsValues;
    };

    template <class T>
    inline void connect(VarListener & listener, const Link<T> & link) {
        const auto & var = *link.getVars().GetFirst();
        VarDispatcher<T>::instance().connect(var, listener);
    }

    template <class T, class TT, class ... TS>
    inline void connect(VarListener & listener, const Link<T, TT, TS ...> & link) {
        const auto & var = *link.getVars().GetFirst();
        VarDispatcher<T>::instance().connect(var, listener);
        connect(listener, Link<TT, TS ...>(*link.getVars().Next()));
    }

    template <class T>
    inline const auto & value(const Var<T> * var, const VarListener & l) {
        return VarDispatcher<T>::instance().value(var, l);
    }

}

#endif // VARDISPATCHER_HPP
