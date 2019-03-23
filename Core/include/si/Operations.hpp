
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
        return unit<DivDim<NoDim, D>, C> { lhs * rhs.val() };
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


    // template<class L, class R>
    // auto operator*(const L &lhs, const R &rhs)
    // {
    //     using dim = MulDim<typename L::dim_type, typename R::dim_type>;
    //     return Value<dim>{lhs.val() * rhs.val()};
    // }

    // template<class V>
    // V operator*(const double lhs, const V &rhs)
    // {
    //     return V { lhs * rhs.val() };
    // }

    // template<class V>
    // V operator*(const V &lhs, const double rhs)
    // {
    //     return V { lhs.val() * rhs };
    // }

    // template<class L, class R>
    // auto operator/(const L &lhs, const R &rhs)
    // {
    //     using dim = DivDim<typename L::dim_type, typename R::dim_type>;
    //     return Value<dim>{lhs.val() / rhs.val()};
    // }

    // template<class V>
    // V operator/(const V &lhs, const double rhs)
    // {
    //     return V { lhs.val() / rhs };
    // }

    // template<class V>
    // auto operator/(const double lhs, const V &rhs)
    // {
    //     using dim = DivDim<NoDim, typename V::dim_type>;
    //     return Value<dim_set> { lhs.val() / rhs };
    // }

    // template<class V>
    // double operator+(const V &lhs, const V &rhs)
    // {
    //     return lhs.val() / rhs.val();
    // }

    // template<class V>
    // V operator+(const V &lhs, const V &rhs)
    // {
    //     return V {lhs.val() + rhs.val()};
    // }

    // template<class V>
    // V operator-(const V &lhs, const V &rhs)
    // {
    //     return V {lhs.val() - rhs.val()};
    // }

    // template<class V, int Num, int Den=1>
    // auto pow(const V &val)
    // {
    //     using dim = PowDim<V::dim_type, Num, Den>;
    //     return Value<dim> { std::pow(val(), Num / static_cast<double>(Den)) };
    // }

    // template<class V>
    // auto square(const V &val)
    // {
    //     return pow<V, 2, 1>(val);
    // }

    // template<class V>
    // auto cube(const V &val)
    // {
    //     return pow<V, 3, 1>(val);
    // }

    // template<class V>
    // auto sqrt(const V &val)
    // {
    //     return pow<V, 1, 2>(val);
    // }

    // template<class V>
    // auto cbrt(const V &val)
    // {
    //     return pow<V, 1, 3>(val);
    // }

}
