
#pragma once

#include "Value.hpp"

#include <cmath>

namespace si {

    template<typename LhsD, typename RhsD>
    struct MulDim
    {
        static_assert(LhsD::base_dim == RhsD::base_dim);

        // 1/1  +  1/1   =   2/1
        // 1/2  +  1/2   =   4/4 = 1/1
        // 1/1  +  1/2   =   3/2
        // 1/3  +  1/2   =   5/6

        static constexpr int num = LhsD::num * RhsD::den + RhsD::num * LhsD::den;
        static constexpr int den = LhsD::den * RhsD::den;
        static constexpr int gcd = std::gcd(num, den);

        using type = Dim<
            LhsD::base_dim,
            num / gcd,
            den / gcd
        >;
    };


    template<typename LhsDS, typename RhsDS>
    struct MulDimSet
    {
        using type = DimSet<
            typename MulDim<typename LhsDS::mass, typename RhsDS::mass>::type,
            typename MulDim<typename LhsDS::length, typename RhsDS::length>::type,
            typename MulDim<typename LhsDS::time, typename RhsDS::time>::type,
            typename MulDim<typename LhsDS::current, typename RhsDS::current>::type,
            typename MulDim<typename LhsDS::temperature, typename RhsDS::temperature>::type,
            typename MulDim<typename LhsDS::amount, typename RhsDS::amount>::type,
            typename MulDim<typename LhsDS::light_intensity, typename RhsDS::light_intensity>::type
        >;
    };

    template<typename LhsD, typename RhsD>
    struct DivDim
    {
        static_assert(LhsD::base_dim == RhsD::base_dim);

        // 1/1  -  1/1   =   0/1
        // 1/2  -  1/2   =   0/4 = 0/1
        // 1/1  -  1/2   =   1/2
        // 1/3  -  1/2   =   1/6

        static constexpr int num = LhsD::num * RhsD::den - RhsD::num * LhsD::den;
        static constexpr int den = LhsD::den * RhsD::den;
        static constexpr int gcd = std::gcd(num, den);

        using type = Dim<
            LhsD::base_dim,
            num / gcd,
            den / gcd
        >;
    };

    template<typename LhsDS, typename RhsDS>
    struct DivDimSet
    {
        using type = DimSet<
            typename DivDim<typename LhsDS::mass, typename RhsDS::mass>::type,
            typename DivDim<typename LhsDS::length, typename RhsDS::length>::type,
            typename DivDim<typename LhsDS::time, typename RhsDS::time>::type,
            typename DivDim<typename LhsDS::current, typename RhsDS::current>::type,
            typename DivDim<typename LhsDS::temperature, typename RhsDS::temperature>::type,
            typename DivDim<typename LhsDS::amount, typename RhsDS::amount>::type,
            typename DivDim<typename LhsDS::light_intensity, typename RhsDS::light_intensity>::type
        >;
    };

    template<typename D, int Num, int Den>
    struct PowDim
    {
        // 1/2  +  3/2   =   8/4 = 2/1

        static constexpr int num = D::num * Den + num * D::den;
        static constexpr int den = D::den * Den;
        static constexpr int gcd = std::gcd(num, den);

        using type = Dim<
            D::base_dim,
            num / gcd,
            den / gcd
        >;
    };

    template<typename DS, int Num, int Den>
    struct PowDimSet
    {
        using type = DimSet<
            typename PowDim<typename DS::mass, Num, Den>::type,
            typename PowDim<typename DS::length, Num, Den>::type,
            typename PowDim<typename DS::time, Num, Den>::type,
            typename PowDim<typename DS::current, Num, Den>::type,
            typename PowDim<typename DS::temperature, Num, Den>::type,
            typename PowDim<typename DS::amount, Num, Den>::type,
            typename PowDim<typename DS::light_intensity, Num, Den>::type
        >;
    };

    template<class L, class R>
    auto operator*(const L &lhs, const R &rhs)
    {
        using dim_set = MulDimSet<L::dim_set, R::dim_set>::type;
        return Value<dim_set>{lhs.val() * rhs.val()};
    }

    template<class V>
    V operator*(const double lhs, const V &rhs)
    {
        return V { lhs * rhs.val() };
    }

    template<class V>
    V operator*(const V &lhs, const double rhs)
    {
        return V { lhs.val() * rhs };
    }

    template<class L, class R>
    auto operator/(const L &lhs, const R &rhs)
    {
        using dim_set = DivDimSet<L::dim_set, R::dim_set>::type;
        return Value<dim_set>{lhs.val() / rhs.val()};
    }

    template<class V>
    V operator/(const V &lhs, const double rhs)
    {
        return V { lhs.val() / rhs };
    }

    template<class V>
    V operator/(const double lhs, const V &rhs)
    {
        using dim_set = DivDimSet<NoDimSet, V::dim_set>::type;
        return Value<dim_set> { lhs.val() / rhs };
    }

    template<class V>
    double operator+(const V &lhs, const V &rhs)
    {
        return lhs.val() / rhs.val();
    }

    template<class V>
    V operator+(const V &lhs, const V &rhs)
    {
        return V {lhs.val() + rhs.val()};
    }

    template<class V>
    V operator-(const V &lhs, const V &rhs)
    {
        return V {lhs.val() - rhs.val()};
    }

    template<class V, int Num, int Den=1>
    auto pow(const V &val)
    {
        using dim_set = PowDim<V::dim_set, Num, Den>;
        return Value<dim_set> { std::pow(val(), Num / static_cast<double>(Den)) };
    }

    template<class V>
    auto square(const V &val)
    {
        return pow<V, 2, 1>(val);
    }

    template<class V>
    auto cube(const V &val)
    {
        return pow<V, 3, 1>(val);
    }

    template<class V>
    auto sqrt(const V &val)
    {
        return pow<V, 1, 2>(val);
    }

    template<class V>
    auto cbrt(const V &val)
    {
        return pow<V, 1, 3>(val);
    }

}
