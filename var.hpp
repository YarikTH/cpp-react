#ifndef VAR_HPP
#define VAR_HPP

#include <utility>

namespace react {

    template <class T>
    class Var {
    public:
        using StoredType = T;

        Var() = default;
        Var(const StoredType & newValue):
            value(newValue) {
        }
        Var(StoredType && newValue):
            value(std::move(newValue)) {
        }

        Var & operator= (const StoredType & newValue) {
            value = newValue;
            // TODO: implement change notification
            return *this;
        }
        Var & operator= (StoredType && newValue) {
            value = std::move(newValue);
            // TODO: implement change notification
            return *this;
        }

        const StoredType & getValue() const {
            return value;
        }

        operator const StoredType & () {
            return value;
        }

    private:
        StoredType value = StoredType{};
    };

    template <class T>
    inline Var<T> makeVar(const T & value) {
        return Var<T>(value);
    }

    template <class T>
    inline Var<T> makeVar(T && value) {
        return Var<T>(std::move(value));
    }

} // namespace react

#endif // VAR_HPP
