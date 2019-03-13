
#pragma once

#include "Dim.hpp"
#include "Value.hpp"

#include <cmath>

namespace si {

    // operations on base dimension

    namespace base {

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

    // operations on dimensions

    template<typename LhsD, typename RhsD>
    using MulDim = Dim<
        typename base::MulDim<typename LhsD::mass, typename RhsD::mass>,
        typename base::MulDim<typename LhsD::length, typename RhsD::length>,
        typename base::MulDim<typename LhsD::time, typename RhsD::time>,
        typename base::MulDim<typename LhsD::current, typename RhsD::current>,
        typename base::MulDim<typename LhsD::temperature, typename RhsD::temperature>,
        typename base::MulDim<typename LhsD::amount, typename RhsD::amount>,
        typename base::MulDim<typename LhsD::light_intensity, typename RhsD::light_intensity>
    >;

    template<typename LhsD, typename RhsD>
    using DivDim = Dim<
        typename base::DivDim<typename LhsD::mass, typename RhsD::mass>,
        typename base::DivDim<typename LhsD::length, typename RhsD::length>,
        typename base::DivDim<typename LhsD::time, typename RhsD::time>,
        typename base::DivDim<typename LhsD::current, typename RhsD::current>,
        typename base::DivDim<typename LhsD::temperature, typename RhsD::temperature>,
        typename base::DivDim<typename LhsD::amount, typename RhsD::amount>,
        typename base::DivDim<typename LhsD::light_intensity, typename RhsD::light_intensity>
    >;

    template<typename D, int Num, int Den>
    using PowDim = Dim<
        typename base::PowDim<typename D::mass, Num, Den>,
        typename base::PowDim<typename D::length, Num, Den>,
        typename base::PowDim<typename D::time, Num, Den>,
        typename base::PowDim<typename D::current, Num, Den>,
        typename base::PowDim<typename D::temperature, Num, Den>,
        typename base::PowDim<typename D::amount, Num, Den>,
        typename base::PowDim<typename D::light_intensity, Num, Den>
    >;

    // operations on conversions

    // unit operations
    template<class L, class R>
    auto operator*(const L &lhs, const R &rhs)
    {
        using dim = MulDim<typename L::dim_type, typename R::dim_type>;
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
