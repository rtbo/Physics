
#pragma once

#include "Dim.hpp"
#include "Value.hpp"
#include "Unit.hpp"

#include <cmath>

namespace si {
    namespace detail {

        // operations on conversions
        template<typename Lhs, typename Rhs>
        struct MulConvHelper
        {
            static_assert(is_conv<Lhs>() && is_conv<Rhs>());
        };

        template<>
        struct MulConvHelper<identity_conv, identity_conv>
        {
            using type = identity_conv;
        };

        template<typename R>
        struct MulConvHelper<factor_conv<R>, identity_conv>
        {
            using type = factor_conv<R>;
        };

        template<typename R>
        struct MulConvHelper<identity_conv, factor_conv<R>>
        {
            using type = factor_conv<R>;
        };

        template<typename LR, typename RR>
        struct MulConvHelper<factor_conv<LR>, factor_conv<RR>>
        {
            using type = factor_conv<std::ratio_multiply<LR, RR>>;
        };

        template<typename Lhs, typename Rhs>
        using MulConv = typename MulConvHelper<Lhs, Rhs>::type;

        template<typename Lhs, typename Rhs>
        using MulUnit = unit<
            MulDim<typename Lhs::dim_type, typename Rhs::dim_type>,
            MulConv<typename Lhs::conv_type, typename Rhs::conv_type>
        >;

        template<typename Lhs, typename Rhs>
        using MulValue = Value<
            MulDim<typename Lhs::dim_type, typename Rhs::dim_type>
        >;
    }

    // unit operations

    // equality
    template<typename D, typename LhsC, typename RhsC>
    constexpr bool
    operator==(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() == rhs.repr();
    }

    template<typename D, typename C>
    constexpr bool
    operator==(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() == rhs.val();
    }

    // inequality
    template<typename D, typename LhsC, typename RhsC>
    constexpr bool
    operator!=(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() != rhs.repr();
    }

    template<typename D, typename C>
    constexpr bool
    operator!=(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() != rhs.val();
    }

    // lower or equal
    template<typename D, typename LhsC, typename RhsC>
    constexpr bool
    operator<=(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() <= rhs.repr();
    }

    template<typename D, typename C>
    constexpr bool
    operator<=(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() <= rhs.val();
    }

    // greater or equal
    template<typename D, typename LhsC, typename RhsC>
    constexpr bool
    operator>=(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() >= rhs.repr();
    }

    template<typename D, typename C>
    constexpr bool
    operator>=(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() >= rhs.val();
    }

    // lower
    template<typename D, typename LhsC, typename RhsC>
    constexpr bool
    operator<(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() < rhs.repr();
    }

    template<typename D, typename C>
    constexpr bool
    operator<(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() < rhs.val();
    }

    // greater
    template<typename D, typename LhsC, typename RhsC>
    constexpr bool
    operator>(const unit<D, LhsC> &lhs, const unit<D, RhsC> &rhs)
    {
        return lhs.repr() > rhs.repr();
    }

    template<typename D, typename C>
    constexpr bool
    operator>(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return lhs.val() > rhs.val();
    }

    // unary
    template<class U>
    constexpr
    std::enable_if_t<is_unit<U>(), U>
    operator-(const U &u)
    {
        return U { -u.val() };
    }

    template<class Lhs, class Rhs>
    constexpr
    std::enable_if_t<is_unit<Lhs>() && is_unit<Rhs>(), detail::MulUnit<Lhs, Rhs>>
    operator*(const Lhs &lhs, const Rhs &rhs)
    {
        return detail::MulUnit<Lhs, Rhs> { lhs.val() * rhs.val() };
    }

    // value operations

    // comparison
    template<class D>
    constexpr bool
    operator==(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) == value_repr(rhs);
    }

    template<class D>
    constexpr bool
    operator!=(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) != value_repr(rhs);
    }

    template<class D>
    constexpr bool
    operator<=(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) <= value_repr(rhs);
    }

    template<class D>
    constexpr bool
    operator>=(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) >= value_repr(rhs);
    }

    template<class D>
    constexpr bool
    operator<(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) < value_repr(rhs);
    }

    template<class D>
    constexpr bool
    operator>(const Value<D> &lhs, const Value<D> &rhs)
    {
        return value_repr(lhs) > value_repr(rhs);
    }

    // operations

    template<class D>
    constexpr Value<D>
    operator-(const Value<D> &v)
    {
        return Value<D> { -value_repr(v) };
    }


    template<typename LhsD, typename RhsD>
    constexpr Value<MulDim<LhsD, RhsD>>
    operator*(const Value<LhsD> &lhs, const Value<RhsD> &rhs)
    {
        return Value<MulDim<LhsD, RhsD>> { value_repr(lhs) * value_repr(rhs) };
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
