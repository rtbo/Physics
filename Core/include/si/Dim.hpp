
#pragma once

#include "Value.hpp"

#include <numeric>
#include <ratio>

namespace si {

    namespace detail {
        template<typename T>
        struct is_ratio_helper : std::false_type {};

        template<intmax_t N, intmax_t D>
        struct is_ratio_helper<std::ratio<N, D> > : std::true_type {};

        template<typename R>
        constexpr bool is_ratio()
        {
            return is_ratio_helper<R>::value;
        }

        template<typename R>
        constexpr double ratio_double()
        {
            static_assert(is_ratio<R>());
            return R::num / static_cast<double>(R::den);
        }
    }

    namespace base {
        // according International System of Units, there are 7 base dimensions
        // all other values (pressure, energy, voltage...) are derived from these 7 dimensions

        enum class DimName {
            Mass,           //< Main unit: kilogram - symbol M
            Length,         //< Main unit: meter    - symbol L
            Time,           //< Main unit: second   - symbol T
            Current,        //< Main unit: ampere   - symbol I - electrical current
            Temperature,    //< Main unit: kelvin   - symbol Theta
            Amount,         //< Main unit: mole     - symbol N - amount of substance
            LightIntensity, //< Main unit: candela  - symbol J
        };

        template<DimName D, typename R>
        struct Dim
        {
            static_assert(si::detail::is_ratio<R>(), "si::base::Dim must be used with std::ratio");
            static constexpr DimName name = D;
            using ratio = R;
        };

        template<int Num, int Den=1>
        using Mass = Dim<DimName::Mass, std::ratio<Num, Den> >;

        template<int Num, int Den=1>
        using Length = Dim<DimName::Length, std::ratio<Num, Den> >;

        template<int Num, int Den=1>
        using Time = Dim<DimName::Time, std::ratio<Num, Den> >;

        template<int Num, int Den=1>
        using Current = Dim<DimName::Current, std::ratio<Num, Den> >;

        template<int Num, int Den=1>
        using Temperature = Dim<DimName::Temperature, std::ratio<Num, Den> >;

        template<int Num, int Den=1>
        using Amount = Dim<DimName::Amount, std::ratio<Num, Den> >;

        template<int Num, int Den=1>
        using LightIntensity = Dim<DimName::LightIntensity, std::ratio<Num, Den> >;

        using NoMass = Mass<0>;
        using NoLength = Length<0>;
        using NoTime = Time<0>;
        using NoCurrent = Current<0>;
        using NoTemperature = Temperature<0>;
        using NoAmount = Amount<0>;
        using NoLightIntensity = LightIntensity<0>;

        namespace detail {
            template<typename T>
            struct is_dim_helper : std::false_type
            {};

            template<base::DimName N, typename R>
            struct is_dim_helper<Dim<N, R>> : std::true_type
            {};
        }

        template<typename D>
        constexpr bool is_dim()
        {
            return detail::is_dim_helper<D>::value;
        }

        template<typename D>
        constexpr bool is_mass_dim()
        {
            return is_dim<D>() && D::name == DimName::Mass;
        }

        template<typename D>
        constexpr bool is_length_dim()
        {
            return is_dim<D>() && D::name == DimName::Length;
        }

        template<typename D>
        constexpr bool is_time_dim()
        {
            return is_dim<D>() && D::name == DimName::Time;
        }

        template<typename D>
        constexpr bool is_current_dim()
        {
            return is_dim<D>() && D::name == DimName::Current;
        }

        template<typename D>
        constexpr bool is_temperature_dim()
        {
            return is_dim<D>() && D::name == DimName::Temperature;
        }

        template<typename D>
        constexpr bool is_amount_dim()
        {
            return is_dim<D>() && D::name == DimName::Amount;
        }

        template<typename D>
        constexpr bool is_light_intensity_dim()
        {
            return is_dim<D>() && D::name == DimName::LightIntensity;
        }

    }

    template<typename M=base::NoMass,
             typename L=base::NoLength,
             typename T=base::NoTime,
             typename I=base::NoCurrent,
             typename Th=base::NoTemperature,
             typename N=base::NoAmount,
             typename J=base::NoLightIntensity>
    struct Dim
    {
        static_assert(base::is_mass_dim<M>());
        static_assert(base::is_length_dim<L>());
        static_assert(base::is_time_dim<T>());
        static_assert(base::is_current_dim<I>());
        static_assert(base::is_temperature_dim<Th>());
        static_assert(base::is_amount_dim<N>());
        static_assert(base::is_light_intensity_dim<J>());

        using mass = M;
        using length = L;
        using time = T;
        using current = I;
        using temperature = Th;
        using amount = N;
        using light_intensity = J;
    };

    using NoDim = Dim<>;

    namespace detail {
        template<typename T>
        struct is_dim_helper : std::false_type
        {};

        template<typename M, typename L, typename T, typename I, typename Th, typename N, typename J>
        struct is_dim_helper<Dim<M, L, T, I, Th, N, J>> : std::true_type
        {};
    }

    template<typename D>
    constexpr bool is_dim()
    {
        return detail::is_dim_helper<D>::value;
    }


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

}
