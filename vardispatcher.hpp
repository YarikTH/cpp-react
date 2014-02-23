#pragma once

#ifndef VARDISPATCHER_HPP
#define VARDISPATCHER_HPP

#include <unordered_set>
#include <unordered_map>
#include "varlistener.hpp"
#include "link.hpp"

namespace react {

    template <class T>
    class Var;

    template <class T>
    class VarDispatcher {
    public:
        using VarT = Var<T>;
        using Listeners = std::unordered_set<VarListener *>;
        using VarsListeners = std::unordered_map<const VarT *, Listeners>;

        static auto & instance() {
            static VarDispatcher dispatcher;
            return dispatcher;
        }

        void connect(const VarT & var) {
            varsListeners[&var];
        }

        void connect(const VarT & var, VarListener & listener) {
            auto listeners = varsListeners.find(&var);

            if (listeners != varsListeners.end()) {
                listeners->second.insert(&listener);
            }
            else {
                // error, we are not owninng this var
            }
        }

        void disconnect(const VarT & var) {
            varsListeners.erase(&var);
        }

        void disconnect(const VarT & var, VarListener & listener) {
            auto listeners = varsListeners.find(&var);

            if (listeners != varsListeners.end()) {
                listeners->second.erase(&listener);
            }
            else {
                // error, we are not owninng this var
            }
        }

        void notifyChange(const VarT & var) {
            auto listeners = varsListeners.find(&var);

            if (listeners != varsListeners.end()) {
                for (auto & listener : listeners->second) {
                    listener->update();
                }
            }
            else {
                // error, we are not owninng this var
            }
        }

        const T & value(const VarT * var) {
            auto it = varsListeners.find(var);

            if (it != varsListeners.end()) {
                return (*var)();
            }
            else {
                // TODO implement value caching for destroyed vars
                static auto res = T{};
                return res;
            }
        }

    private:
        VarDispatcher() = default;

        VarsListeners varsListeners;
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
    inline const auto & value(const Var<T> * var) {
        return VarDispatcher<T>::instance().value(var);
    }

}

#endif // VARDISPATCHER_HPP
