#ifndef RX_HPP
#define RX_HPP

#include "var.hpp"
#include <functional>

namespace react {

    template <class T1, class T2, class CALLABLE>
    class Rx : public Var<T1> {
    public:
        using StoredType = T1;
        using SourceType = T2;
        using Source = Var<SourceType>;

        Rx(const Source & source, CALLABLE newFunction):
            function(newFunction) {
            // TODO: implement connection
        }
        virtual ~Rx() {
            // TODO: implement disconnection
        }

    private:
        CALLABLE function;
    };

    template <class T, class CALLABLE>
    auto makeRx(const Var<T> & source,
                CALLABLE function) ->
        Rx<decltype(function(source.getValue())), T, CALLABLE> {

        using Result = Rx<decltype(function(source.getValue())), T, CALLABLE>;
        return Result(source, function);
    }

} // namespace react

#endif // RX_HPP
