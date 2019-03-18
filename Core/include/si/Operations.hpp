
#pragma once

#include "Dim.hpp"
#include "Value.hpp"
#include "Unit.hpp"

#include <cmath>

namespace si {

    namespace base {
        // operations on base dimension

        namespace detail {

            template<typename LhsD, typename RhsD>
            struct EnforceSameName
            {
                static_assert(LhsD::name == RhsD::name);
                static constexpr DimName name = LhsD::name;
            };

            template<typename LhsD, typename RhsD>
            using MulDim = Dim<
                EnforceSameName<LhsD, RhsD>::name,
                std::ratio_add<typename LhsD::ratio, typename RhsD::ratio>
            >;

            template<typename LhsD, typename RhsD>
            using DivDim = Dim<
                EnforceSameName<LhsD, RhsD>::name,
                std::ratio_subtract<typename LhsD::ratio, typename RhsD::ratio>
            >;

            template<typename D, int Num, int Den>
            using PowDim = Dim<
                D::name,
                std::ratio_add<typename D::ratio, std::ratio<Num, Den> >
            >;
        }
    }

    namespace detail {
        // operations on dimensions

        template<typename LhsD, typename RhsD>
        using MulDim = Dim<
            typename base::detail::MulDim<typename LhsD::mass, typename RhsD::mass>,
            typename base::detail::MulDim<typename LhsD::length, typename RhsD::length>,
            typename base::detail::MulDim<typename LhsD::time, typename RhsD::time>,
            typename base::detail::MulDim<typename LhsD::current, typename RhsD::current>,
            typename base::detail::MulDim<typename LhsD::temperature, typename RhsD::temperature>,
            typename base::detail::MulDim<typename LhsD::amount, typename RhsD::amount>,
            typename base::detail::MulDim<typename LhsD::light_intensity, typename RhsD::light_intensity>
        >;

        template<typename LhsD, typename RhsD>
        using DivDim = Dim<
            typename base::detail::DivDim<typename LhsD::mass, typename RhsD::mass>,
            typename base::detail::DivDim<typename LhsD::length, typename RhsD::length>,
            typename base::detail::DivDim<typename LhsD::time, typename RhsD::time>,
            typename base::detail::DivDim<typename LhsD::current, typename RhsD::current>,
            typename base::detail::DivDim<typename LhsD::temperature, typename RhsD::temperature>,
            typename base::detail::DivDim<typename LhsD::amount, typename RhsD::amount>,
            typename base::detail::DivDim<typename LhsD::light_intensity, typename RhsD::light_intensity>
        >;

        template<typename D, int Num, int Den>
        using PowDim = Dim<
            typename base::detail::PowDim<typename D::mass, Num, Den>,
            typename base::detail::PowDim<typename D::length, Num, Den>,
            typename base::detail::PowDim<typename D::time, Num, Den>,
            typename base::detail::PowDim<typename D::current, Num, Den>,
            typename base::detail::PowDim<typename D::temperature, Num, Den>,
            typename base::detail::PowDim<typename D::amount, Num, Den>,
            typename base::detail::PowDim<typename D::light_intensity, Num, Den>
        >;

        // operations on conversions
        template<typename Lhs, typename Rhs>
        struct MulConvHelper
        {
            static_assert(is_conv<Lhs>() && is_conv<Rhs>());
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
    template<class Lhs, class Rhs>
    constexpr
    std::enable_if_t<are_compatible_units<Lhs, Rhs>(), bool>
    operator==(const Lhs &lhs, const Rhs &rhs)
    {
        return lhs.repr() == rhs.repr();
    }

    template<class U>
    constexpr
    std::enable_if_t<is_unit<U>(), bool>
    operator==(const U &lhs, const U &rhs)
    {
        return lhs.val() == rhs.val();
    }

    // inequality
    template<class Lhs, class Rhs>
    constexpr
    std::enable_if_t<are_compatible_units<Lhs, Rhs>(), bool>
    operator!=(const Lhs &lhs, const Rhs &rhs)
    {
        return lhs.repr() != rhs.repr();
    }

    template<class U>
    constexpr
    std::enable_if_t<is_unit<U>(), bool>
    operator!=(const U &lhs, const U &rhs)
    {
        return lhs.val() != rhs.val();
    }

    // lower or equal
    template<class Lhs, class Rhs>
    constexpr
    std::enable_if_t<are_compatible_units<Lhs, Rhs>(), bool>
    operator<=(const Lhs &lhs, const Rhs &rhs)
    {
        return lhs.repr() <= rhs.repr();
    }

    template<class U>
    constexpr
    std::enable_if_t<is_unit<U>(), bool>
    operator<=(const U &lhs, const U &rhs)
    {
        return lhs.val() <= rhs.val();
    }

    // greater or equal
    template<class Lhs, class Rhs>
    constexpr
    std::enable_if_t<are_compatible_units<Lhs, Rhs>(), bool>
    operator>=(const Lhs &lhs, const Rhs &rhs)
    {
        return lhs.repr() >= rhs.repr();
    }

    template<class U>
    constexpr
    std::enable_if_t<is_unit<U>(), bool>
    operator>=(const U &lhs, const U &rhs)
    {
        return lhs.val() >= rhs.val();
    }

    // lower
    template<class Lhs, class Rhs>
    constexpr
    std::enable_if_t<are_compatible_units<Lhs, Rhs>(), bool>
    operator<(const Lhs &lhs, const Rhs &rhs)
    {
        return lhs.repr() < rhs.repr();
    }

    template<class U>
    constexpr
    std::enable_if_t<is_unit<U>(), bool>
    operator<(const U &lhs, const U &rhs)
    {
        return lhs.val() < rhs.val();
    }

    // greater
    template<class Lhs, class Rhs>
    constexpr
    std::enable_if_t<are_compatible_units<Lhs, Rhs>(), bool>
    operator>(const Lhs &lhs, const Rhs &rhs)
    {
        return lhs.repr() > rhs.repr();
    }

    template<class U>
    constexpr
    std::enable_if_t<is_unit<U>(), bool>
    operator>(const U &lhs, const U &rhs)
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
    template<class V>
    constexpr
    std::enable_if_t<is_value<V>(), bool>
    operator==(const V &lhs, const V &rhs)
    {
        return value_repr(lhs) == value_repr(rhs);
    }

    template<class V>
    constexpr
    std::enable_if_t<is_value<V>(), bool>
    operator!=(const V &lhs, const V &rhs)
    {
        return value_repr(lhs) != value_repr(rhs);
    }

    template<class V>
    constexpr
    std::enable_if_t<is_value<V>(), bool>
    operator<=(const V &lhs, const V &rhs)
    {
        return value_repr(lhs) <= value_repr(rhs);
    }

    template<class V>
    constexpr
    std::enable_if_t<is_value<V>(), bool>
    operator>=(const V &lhs, const V &rhs)
    {
        return value_repr(lhs) >= value_repr(rhs);
    }

    template<class V>
    constexpr
    std::enable_if_t<is_value<V>(), bool>
    operator<(const V &lhs, const V &rhs)
    {
        return value_repr(lhs) < value_repr(rhs);
    }

    template<class V>
    constexpr
    std::enable_if_t<is_value<V>(), bool>
    operator>(const V &lhs, const V &rhs)
    {
        return value_repr(lhs) > value_repr(rhs);
    }

    // operations

    template<class V>
    constexpr
    std::enable_if_t<is_value<V>(), V>
    operator-(const V &v)
    {
        return V { -value_repr(v) };
    }


    template<class Lhs, class Rhs>
    constexpr
    typename std::enable_if<is_value<Lhs>() && is_value<Rhs>(), detail::MulValue<Lhs, Rhs>>::type
    operator*(const Lhs &lhs, const Rhs &rhs)
    {
        return detail::MulValue<Lhs, Rhs> { value_repr(lhs) * value_repr(rhs) };
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
