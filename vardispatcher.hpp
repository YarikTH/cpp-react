#pragma once

#ifndef VARDISPATCHER_HPP
#define VARDISPATCHER_HPP

#include <unordered_set>
#include <unordered_map>
#include "varlistener.hpp"

namespace react {

    template <class T>
    class Var;

    template <class T>
    class VarDispatcher {
    public:
        using VarT = Var<T>;
        using Listeners = std::unordered_set<VarListener *>;
        using VarsListeners = std::unordered_map<const VarT *, Listeners>;

        static auto & instance();

        void connect(const VarT & var) {
            varsListeners[&var];
        }

        void connect(const VarT & var, VarListener & listener) {
            varsListeners[&var].insert(&listener);
        }

        void disconnect(const VarT & var) {
            varsListeners.erase(&var);
        }

        void disconnect(const VarT & var, VarListener & listener) {
            varsListeners[&var].erase(&listener);
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
                return var->getValue();
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
    auto & VarDispatcher<T>::instance() {
        static VarDispatcher dispatcher;
        return dispatcher;
    }

    inline void connect(VarListener &) {
    }

    template <class T, class ... TS>
    inline void connect(VarListener & listener,
                        const Var<T> & var,
                        const Var<TS> & ... vars) {
        VarDispatcher<T>::instance().connect(var, listener);
        connect(listener, vars ...);
    }

    template <class T>
    inline const auto & value(const Var<T> * var) {
        return VarDispatcher<T>::instance().value(var);
    }

}

#endif // VARDISPATCHER_HPP
