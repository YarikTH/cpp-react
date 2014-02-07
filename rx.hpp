#ifndef RX_HPP
#define RX_HPP

#include "var.hpp"
#include <functional>

namespace react {

    template <class T, class SOURCE_T, class CALLABLE>
    class Rx : public Var<T> {
    public:
        using StoredType = T;
        using SourceType = SOURCE_T;
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

    template <class SOURCE_T, class CALLABLE>
    auto makeRx(const Var<SOURCE_T> & source,
                CALLABLE function) ->
        Rx<decltype(function(source.getValue())), SOURCE_T, CALLABLE> {

        using Result = Rx<decltype(function(source.getValue())), SOURCE_T, CALLABLE>;
        return Result(source, function);
    }

} // namespace react

#endif // RX_HPP
