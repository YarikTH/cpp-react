#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>

namespace react {

    class VarListener;

    template <class T>
    class Var;

    template <class T, class FN, class ... TS>
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

    template <class T>
    class NotConnectedType {
    public:
        using Type = NotConnected;
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

    template <class T, class FN, class ... TS>
    class NotConnectedType<Rx<T, FN, TS ...>> {
    public:
        using Type = RxNotConnected;
    };

    template <class T>
    class AlreadyConnectedType {
    public:
        using Type = AlreadyConnected;
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
