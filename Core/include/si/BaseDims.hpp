
#pragma once

#include "Value.hpp"

#include <numeric>

namespace si {

    // according Internation System of Units, there are 7 base dimensions
    // all other values (pressure, energy, voltage...) are derived from these 7 dimensions

    enum class BaseDim {
        Mass,           //< Main unit: kilogram - symbol M
        Length,         //< Main unit: meter    - symbol L
        Time,           //< Main unit: second   - symbol T
        Current,        //< Main unit: ampere   - symbol I - electrical current
        Temperature,    //< Main unit: kelvin   - symbol Theta
        Amount,         //< Main unit: mole     - symbol N - amount of substance
        LightIntensity, //< Main unit: candela  - symbol J
    };

    template<BaseDim D, int Num=1, int Den=1>
    struct Dim
    {
        static constexpr BaseDim base_dim = D;
        static constexpr int num = Num;
        static constexpr int den = Den;
    };

    template<int Num, int Den=1>
    using MassDim = Dim<BaseDim::Mass, Num, Den>;

    template<int Num, int Den=1>
    using LengthDim = Dim<BaseDim::Length, Num, Den>;

    template<int Num, int Den=1>
    using TimeDim = Dim<BaseDim::Time, Num, Den>;

    template<int Num, int Den=1>
    using CurrentDim = Dim<BaseDim::Current, Num, Den>;

    template<int Num, int Den=1>
    using TemperatureDim = Dim<BaseDim::Temperature, Num, Den>;

    template<int Num, int Den=1>
    using AmountDim = Dim<BaseDim::Amount, Num, Den>;

    template<int Num, int Den=1>
    using LightIntensityDim = Dim<BaseDim::LightIntensity, Num, Den>;

    using NoMassDim = MassDim<0>;
    using NoLengthDim = LengthDim<0>;
    using NoTimeDim = TimeDim<0>;
    using NoCurrentDim = CurrentDim<0>;
    using NoTemperatureDim = TemperatureDim<0>;
    using NoAmountDim = AmountDim<0>;
    using NoLightIntensityDim = LightIntensityDim<0>;

    template<typename M=NoMassDim,
             typename L=NoLengthDim,
             typename T=NoTimeDim,
             typename I=NoCurrentDim,
             typename P=NoTemperatureDim,
             typename N=NoAmountDim,
             typename J=NoLightIntensityDim>
    struct DimSet
    {
        static_assert(M::base_dim == BaseDim::Mass);
        static_assert(L::base_dim == BaseDim::Length);
        static_assert(T::base_dim == BaseDim::Time);
        static_assert(I::base_dim == BaseDim::Current);
        static_assert(P::base_dim == BaseDim::Temperature);
        static_assert(N::base_dim == BaseDim::Amount);
        static_assert(J::base_dim == BaseDim::LightIntensity);

        using mass = M;
        using length = L;
        using time = T;
        using current = I;
        using temperature = P;
        using amount = N;
        using light_intensity = J;
    };

    using NoDimSet = DimSet<>;

    using MassDimSet = DimSet<
        MassDim<1>
    >;

    using LengthDimSet = DimSet<
        NoMassDim, LengthDim<1>
    >;

    using TimeDimSet = DimSet<
        NoMassDim, NoLengthDim, TimeDim<1>
    >;

    using CurrentDimSet = DimSet<
        NoMassDim, NoLengthDim, NoTimeDim, CurrentDim<1>
    >;

    using TemperatureDimSet = DimSet<
        NoMassDim, NoLengthDim, NoTimeDim, NoCurrentDim, TemperatureDim<1>
    >;

    using AmountDimSet = DimSet<
        NoMassDim, NoLengthDim, NoTimeDim, NoCurrentDim, NoTemperatureDim, AmountDim<1>
    >;

    using LightIntensityDimSet = DimSet<
        NoMassDim, NoLengthDim, NoTimeDim, NoCurrentDim, NoTemperatureDim, NoAmountDim, LightIntensityDim<1>
    >;


    using Mass = Value<MassDimSet>;
    using Length = Value<LengthDimSet>;
    using Time = Value<TimeDimSet>;
    using Current = Value<CurrentDimSet>;
    using Temperature = Value<TemperatureDimSet>;
    using Amount = Value<AmountDimSet>;
    using LightIntensity = Value<LightIntensityDimSet>;

}
