#pragma once

#ifndef VARDISPATCHER_HPP
#define VARDISPATCHER_HPP

#include <list>
#include <unordered_map>
#include "varlistener.hpp"

namespace react {

    template <class T>
    class Var;

    template <class T>
    class VarDispatcher {
    public:
        using Var = Var<T>;
        using Listeners = std::list<VarListener *>;
        using VarsListeners = std::unordered_map<const Var *, Listeners>;

        static auto & instance();

        void connect(const Var & var) {
            varsListeners[&var] = {};
        }

        void disconnect(const Var & var) {
            varsListeners.erase(&var);
        }

        void notifyChange(const Var & var) {
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

    private:
        VarDispatcher() = default;

        VarsListeners varsListeners;
    };

    template <class T>
    auto & VarDispatcher<T>::instance() {
        static VarDispatcher dispatcher;
        return dispatcher;
    }

}

#endif // VARDISPATCHER_HPP
