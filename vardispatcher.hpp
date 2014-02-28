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
        using Vars = std::unordered_set<const VarT *>;
        using VarsVars = std::unordered_map<const VarT *, const VarT *>;

        using VarsListeners = std::unordered_map<const VarT *, Listeners>;
        using ListenersVarsVars = std::unordered_map<VarListener *, VarsVars>;

        using VarsValues = std::unordered_map<const VarT *, T>;
        using ListenersVarsValues = std::unordered_map<const VarListener *, VarsValues>;

        static auto & instance() {
            static VarDispatcher dispatcher;
            return dispatcher;
        }

        void connect(const VarT & v) {
            set(varsListeners, &v, Listeners{});
        }

        void connect(const VarT * v, VarListener & l) {
            try {
                insert(query(varsListeners, v), &l);
            }
            catch (const VarListenerAlreadyConnected &) {
            }
        }

        void reincarnate(const VarT & from, const VarT & to) {
            auto ifrom = varsListeners.find(&from);
            auto ito = varsListeners.find(&from);

            if (ifrom == varsListeners.end() ||
                ito == varsListeners.end()) {
                throw typename NotConnectedType<VarT>::Type{};
            }

            ito->second = ifrom->second;
            ifrom->second.clear();

            for (auto & l : ito->second) {
                reincarnatedListenersVars[l][&from] = &to;
                l->updateLink();
                reincarnatedListenersVars.erase(l);
            }
        }

        const VarT & reincarnated(const VarT * v, VarListener & l) {
            try {
                return *query(query(reincarnatedListenersVars, &l), v);
            }
            catch (const NotConnected &) {
                query(varsListeners, v);
            }

            return *v;
        }

        void disconnect(const VarT & v) {
            auto it = varsListeners.find(&v);

            if (it == varsListeners.end()) {
                throw typename NotConnectedType<VarT>::Type{};
            }

            for (auto & l : it->second) {
                destroyedVarsValues[l][&v] = v();
            }

            varsListeners.erase(it);
        }

        void disconnect(const VarT * v, VarListener & l) {
            auto varnotfound = true;
            auto it1 = destroyedVarsValues.find(&l);

            if (it1 != destroyedVarsValues.end()) {
                auto it2 = it1->second.find(v);

                if (it2 != it1->second.end()) {
                    varnotfound = false;
                    it1->second.erase(it2);
                }

                if (it1->second.size() == 0) {
                    destroyedVarsValues.erase(it1);
                }
            }

            auto it3 = varsListeners.find(v);

            if (it3 != varsListeners.end()) {
                varnotfound = false;
                auto it4 = it3->second.find(&l);

                if (it4 != it3->second.end()) {
                    it3->second.erase(it4);
                }
            }

            if (varnotfound) {
                throw typename NotConnectedType<VarT>::Type{};
            }
        }

        void notifyChange(const VarT & v) {
            for (auto & l : query(varsListeners, &v)) l->updateValue();
        }

        const T & value(const VarT * v, const VarListener & l) {
            try {
                return query(query(destroyedVarsValues, &l), v);
            }
            catch (const NotConnected &) {
                query(varsListeners, v);
            }

            return (*v)();
        }

    private:
        VarDispatcher() = default;

        VarsListeners varsListeners;
        ListenersVarsValues destroyedVarsValues;
        ListenersVarsVars reincarnatedListenersVars;
    };

}

#endif // VARDISPATCHER_HPP
