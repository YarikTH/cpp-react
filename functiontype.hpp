#ifndef FUNCTIONTYPE_HPP
#define FUNCTIONTYPE_HPP

namespace react {

    template <class FN>
    struct FunctionMemberTypeOwner;

    template <class C, class R, class ... P>
    struct FunctionMemberTypeOwner<R(C::*)(P ...)> {
        using type = R(P ...);
    };

    template <class C, class R, class ... P>
    struct FunctionMemberTypeOwner<R(C::*)(P ...) const> {
        using type = R(P ...);
    };

    template <class FN>
    using FunctionMemberType = typename FunctionMemberTypeOwner<FN>::type;

    template <class FN>
    struct FunctionTypeOwner {
        using type = FunctionMemberType<decltype(&FN::operator())>;
    };

    template <class R, class ... P>
    struct FunctionTypeOwner<R(P ...)> {
        using type = R(P ...);
    };

    template <class R, class ... P>
    struct FunctionTypeOwner<R (*)(P ...)> {
        using type = R(P ...);
    };

    template <class R, class ... P>
    struct FunctionTypeOwner<R (&)(P ...)> {
        using type = R(P ...);
    };

    template <class FN>
    using FunctionType = typename FunctionTypeOwner<FN>::type;

} // namespace react

#endif // FUNCTIONTYPE_HPP
