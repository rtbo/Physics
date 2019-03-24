
#pragma once

#include "Dim.hpp"
#include "Value.hpp"
#include "Unit.hpp"

#include <cmath>

namespace si {

    // unit operations

    // equality
    template<typename D, typename LhsC, typename RhsC>
    inline constexpr bool
    operator==(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() == rhs.repr();
    }

    template<typename D, typename C>
    inline constexpr bool
    operator==(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() == rhs.val();
    }

    // inequality
    template<typename D, typename LhsC, typename RhsC>
    inline constexpr bool
    operator!=(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() != rhs.repr();
    }

    template<typename D, typename C>
    inline constexpr bool
    operator!=(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() != rhs.val();
    }

    // lower or equal
    template<typename D, typename LhsC, typename RhsC>
    inline constexpr bool
    operator<=(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() <= rhs.repr();
    }

    template<typename D, typename C>
    inline constexpr bool
    operator<=(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() <= rhs.val();
    }

    // greater or equal
    template<typename D, typename LhsC, typename RhsC>
    inline constexpr bool
    operator>=(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() >= rhs.repr();
    }

    template<typename D, typename C>
    inline constexpr bool
    operator>=(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() >= rhs.val();
    }

    // lower
    template<typename D, typename LhsC, typename RhsC>
    inline constexpr bool
    operator<(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() < rhs.repr();
    }

    template<typename D, typename C>
    inline constexpr bool
    operator<(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() < rhs.val();
    }

    // greater
    template<typename D, typename LhsC, typename RhsC>
    inline constexpr bool
    operator>(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() > rhs.repr();
    }

    template<typename D, typename C>
    inline constexpr bool
    operator>(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() > rhs.val();
    }

    // unary
    template<typename D, typename C>
    inline constexpr unit<D, C>
    operator-(const unit<D, C> &u)
    {
        return unit<D, C> { -u.val() };
    }

    // mul
    template<typename LD, typename LC, typename RD, typename RC>
    inline constexpr unit<MulDim<LD, RD>, MulConv<LC, RC>>
    operator*(const unit<LD, LC> &lhs, const unit<RD, RC> &rhs)
    {
        return unit<MulDim<LD, RD>, MulConv<LC, RC>> { lhs.val() * rhs.val() };
    }

    template<typename D, typename C>
    inline constexpr unit<D, C>
    operator*(const double &lhs, const unit<D, C> &rhs)
    {
        return unit<D, C> { lhs * rhs.val() };
    }

    template<typename D, typename C>
    inline constexpr unit<D, C>
    operator*(const unit<C, D> &lhs, const double &rhs)
    {
        return unit<D, C> { lhs.val() * rhs };
    }

    // div
    template<typename LD, typename LC, typename RD, typename RC>
    inline constexpr unit<DivDim<LD, RD>, DivConv<LC, RC>>
    operator/(const unit<LD, LC> &lhs, const unit<RD, RC> &rhs)
    {
        return unit<DivDim<LD, RD>, DivConv<LC, RC>> { lhs.val() / rhs.val() };
    }

    template<typename D, typename C>
    inline constexpr unit<DivDim<NoDim, D>, C>
    operator/(const double &lhs, const unit<D, C> &rhs)
    {
        return unit<DivDim<NoDim, D>, C> { lhs / rhs.val() };
    }

    template<typename D, typename C>
    inline constexpr unit<D, C>
    operator/(const unit<C, D> &lhs, const double &rhs)
    {
        return unit<D, C> { lhs.val() / rhs };
    }

    // add
    template<typename D, typename C>
    inline constexpr unit<D, C>
    operator+(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return unit<D, C> { lhs.val() + rhs.val() };
    }

    // sub
    template<typename D, typename C>
    inline constexpr unit<D, C>
    operator-(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return unit<D, C> { lhs.val() - rhs.val() };
    }

    // pow
    template<typename D, typename C, int Exp>
    inline constexpr auto
    pow(const unit<D, C> &val)
    {
        using dim = PowDim<D, Exp, 1>;
        using conv = PowConv<C, Exp>;
        return unit<dim, conv> { std::pow(val.val(), Exp) };
    }

    template<typename D, typename C>
    inline constexpr auto
    square(const unit<D, C> &val)
    {
        return pow<D, C, 2>(val);
    }

    template<typename D, typename C>
    inline constexpr auto
    cube(const unit<D, C> &val)
    {
        return pow<D, C, 3>(val);
    }

    // value operations

    // comparison
    template<class D>
    inline constexpr bool
    operator==(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) == value_repr(rhs);
    }

    template<class D>
    inline constexpr bool
    operator!=(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) != value_repr(rhs);
    }

    template<class D>
    inline constexpr bool
    operator<=(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) <= value_repr(rhs);
    }

    template<class D>
    inline constexpr bool
    operator>=(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) >= value_repr(rhs);
    }

    template<class D>
    inline constexpr bool
    operator<(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) < value_repr(rhs);
    }

    template<class D>
    inline constexpr bool
    operator>(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) > value_repr(rhs);
    }

    // operations

    template<class D>
    inline constexpr Value<D>
    operator-(const Value<D> &v)
    {
        return Value<D> { -value_repr(v) };
    }

    template<typename LD, typename RD>
    inline constexpr Value<MulDim<LD, RD>>
    operator*(const Value<LD> &lhs, const Value<RD> &rhs)
    {
        return Value<MulDim<LD, RD>> { value_repr(lhs) * value_repr(rhs) };
    }

    template<typename D>
    inline constexpr Value<D>
    operator*(const double &lhs, const Value<D> &rhs)
    {
        return Value<D> { lhs * value_repr(rhs) };
    }

    template<typename D>
    inline constexpr Value<D>
    operator*(const Value<D> &lhs, const double &rhs)
    {
        return Value<D> { value_repr(lhs) * rhs };
    }

    template<typename LD, typename RD>
    inline constexpr Value<DivDim<LD, RD>>
    operator/(const Value<LD> &lhs, const Value<RD> &rhs)
    {
        return Value<DivDim<LD, RD>> { value_repr(lhs) / value_repr(rhs) };
    }

    template<typename D>
    inline constexpr Value<DivDim<NoDim, D>>
    operator/(const double &lhs, const Value<D> &rhs)
    {
        return Value<DivDim<NoDim, D>> { lhs / value_repr(rhs) };
    }

    template<typename D>
    inline constexpr Value<D>
    operator/(const Value<D> &lhs, const double &rhs)
    {
        return Value<D> { value_repr(lhs) / rhs };
    }

    template<typename D>
    inline constexpr Value<D>
    operator+(const Value<D> &lhs, const Value<D> &rhs)
    {
        return Value<D> { value_repr(lhs) + value_repr(rhs) };
    }

    template<typename D>
    inline constexpr Value<D>
    operator-(const Value<D> &lhs, const Value<D> &rhs)
    {
        return Value<D> { value_repr(lhs) - value_repr(rhs) };
    }

    template<typename D, int Num, int Den=1>
    inline constexpr auto
    pow(const Value<D> &val)
    {
        using dim = PowDim<D, Num, Den>;
        return Value<dim> {
            default_unit<Value<dim>> {
                std::pow(value_repr().val(), Num / static_cast<double>(Den))
            }
        };
    }

    template<class D>
    inline constexpr auto
    square(const Value<D> &val)
    {
        return pow<D, 2, 1>(val);
    }

    template<class D>
    inline constexpr auto
    cube(const Value<D> &val)
    {
        return pow<D, 3, 1>(val);
    }

    template<class D>
    inline constexpr auto
    sqrt(const Value<D> &val)
    {
        return pow<D, 1, 2>(val);
    }

    template<class D>
    inline constexpr auto
    cbrt(const Value<D> &val)
    {
        return pow<D, 1, 3>(val);
    }
}
