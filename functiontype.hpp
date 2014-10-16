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
