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

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

namespace react {

    class VarListener;

    template <class T>
    class Var;

    template <class T, class ... TS>
    class Rx;

    class NotConnected : public std::exception {
    public:
        virtual const char * what() const throw() override {
            return "error: trying to work with unregistered thing\n";
        }
    };

    class VarNotConnected : public NotConnected {
    public:
        virtual const char * what() const throw() override {
            return "error: trying to work with unregistered Var\n";
        }
    };

    class VarListenerNotConnected : public NotConnected {
    public:
        virtual const char * what() const throw() override {
            return "error: trying to work with unregistered VarListener\n";
        }
    };

    class RxNotConnected : public NotConnected {
    public:
        virtual const char * what() const throw() override {
            return "error: trying to work with unregistered Rx\n";
        }
    };

    class AlreadyConnected : public std::exception {
        virtual const char * what() const throw() override {
            return "error: trying to connect already connected thing\n";
        }
    };

    class VarAlreadyConnected : public AlreadyConnected {
    public:
        virtual const char * what() const throw() override {
            return "error: trying to connect already connected Var\n";
        }
    };

    class VarListenerAlreadyConnected : public AlreadyConnected {
    public:
        virtual const char * what() const throw() override {
            return "error: trying to connect already connected VarListener\n";
        }
    };

    class RxAlreadyConnected : public AlreadyConnected {
    public:
        virtual const char * what() const throw() override {
            return "error: trying to connect already connected Rx\n";
        }
    };

    template <class T>
    class NotConnectedType {
    public:
        using Type = NotConnected;
    };

    template <>
    class NotConnectedType<VarListener *> {
    public:
        using Type = VarListenerNotConnected;
    };

    template <class T>
    class NotConnectedType<Var<T> *> {
    public:
        using Type = VarNotConnected;
    };

    template <class T, class ... TS>
    class NotConnectedType<Rx<T, TS ...> *> {
    public:
        using Type = RxNotConnected;
    };

    template <>
    class NotConnectedType<VarListener> {
    public:
        using Type = VarListenerNotConnected;
    };

    template <class T>
    class NotConnectedType<Var<T>> {
    public:
        using Type = VarNotConnected;
    };

    template <class T, class ... TS>
    class NotConnectedType<Rx<T, TS ...>> {
    public:
        using Type = RxNotConnected;
    };

    template <class T>
    class AlreadyConnectedType {
    public:
        using Type = AlreadyConnected;
    };

    template <>
    class AlreadyConnectedType<VarListener *> {
    public:
        using Type = VarListenerAlreadyConnected;
    };

    template <class T>
    class AlreadyConnectedType<Var<T> *> {
    public:
        using Type = VarAlreadyConnected;
    };

    template <class T, class ... TS>
    class AlreadyConnectedType<Rx<T, TS ...> *> {
    public:
        using Type = RxAlreadyConnected;
    };

    template <>
    class AlreadyConnectedType<VarListener> {
    public:
        using Type = VarListenerAlreadyConnected;
    };

    template <class T>
    class AlreadyConnectedType<Var<T>> {
    public:
        using Type = VarAlreadyConnected;
    };

    template <class T, class ... TS>
    class AlreadyConnectedType<Rx<T, TS ...>> {
    public:
        using Type = RxAlreadyConnected;
    };

    template <class U, class V>
    auto & query(U & map, const V & key) {
        try {
            return map.at(key);
        }
        catch (const std::out_of_range &) {
            throw typename NotConnectedType<V>::Type{};
        }
    }

    template <class U, class V, class W>
    void set(U & map, const V & key, const W & value) {
        if (map.find(key) != map.end()) {
            throw typename AlreadyConnectedType<V>::Type{};
        }

        map[key] = value;
    }

    template <class U, class V>
    void insert(U & set, const V & key) {
        if (set.find(key) != set.end()) {
            throw typename AlreadyConnectedType<V>::Type{};
        }

        set.insert(key);
    }

    template <class U, class V>
    void erase(U & map, const V & key) {
        if (map.find(key) == map.end()) {
            throw typename NotConnectedType<V>::Type{};
        }

        map.erase(key);
    }
}

#endif // EXCEPTIONS_HPP
