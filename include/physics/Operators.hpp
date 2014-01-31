/*
    Copyright (C) 2013-2014 Remi Thebault
    All rights reserved.

    This program and its source code are distributed under the
    terms of the BSD-style license, that can be found in the
    License.txt file at project root.
*/

#ifndef PHYSICS_OPERATORS_HPP
#define PHYSICS_OPERATORS_HPP

#include "Config.hpp"


#include "_IncludeAll.hpp"


namespace Physics {


    // deducing common operators from == and <

    template <class T>
    PHYSICS_CONSTEXPR bool operator!=(const T& lhs, const T& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T>
    PHYSICS_CONSTEXPR bool operator>(const T& lhs, const T& rhs)
    {
        return rhs < lhs;
    }

    template <class T>
    PHYSICS_CONSTEXPR bool operator<=(const T& lhs, const T& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T>
    PHYSICS_CONSTEXPR bool operator>=(const T& lhs, const T& rhs)
    {
        return !(lhs < rhs);
    }



    PHYSICS_CONSTEXPR Area operator*(Length lhs, Length rhs)
    {
        return Area::fromM2(lhs.m() * rhs.m());
    }

    PHYSICS_CONSTEXPR Volume operator*(Length lhs, Area rhs)
    {
        return Volume::fromM3(lhs.m() * rhs.m2());
    }

    PHYSICS_CONSTEXPR Volume operator*(Area lhs, Length rhs)
    {
        return rhs * lhs;
    }



    PHYSICS_CONSTEXPR Velocity operator/(Length lhs, Time rhs)
    {
        return Velocity::fromMps(lhs.m() / rhs.s());
    }

    PHYSICS_CONSTEXPR Acceleration operator/(Velocity lhs, Time rhs)
    {
        return Acceleration::fromMps2(lhs.mps() / rhs.s());
    }



    PHYSICS_CONSTEXPR Flow operator/(Volume lhs, Time rhs)
    {
        return Flow::fromM3ps(lhs.m3() / rhs.s());
    }

    PHYSICS_CONSTEXPR Volume operator*(Flow lhs, Time rhs)
    {
        return Volume::fromM3(lhs.m3ps() * rhs.s());
    }


    PHYSICS_CONSTEXPR Pressure operator/(Force lhs, Area rhs)
    {
        return Pressure::fromPa(lhs.N() / rhs.m2());
    }

    PHYSICS_CONSTEXPR Force operator*(Pressure lhs, Area rhs)
    {
        return Force::fromN(lhs.Pa() * rhs.m2());
    }

    PHYSICS_CONSTEXPR Force operator*(Area lhs, Pressure rhs)
    {
        return rhs * lhs;
    }


    PHYSICS_CONSTEXPR Force operator*(Mass lhs, Acceleration rhs)
    {
        return Force::fromN(lhs.kg() * rhs.mps2());
    }

    PHYSICS_CONSTEXPR Force operator*(Acceleration lhs, Mass rhs)
    {
        return rhs * lhs;
    }



    PHYSICS_CONSTEXPR VolumicMass operator/(Mass lhs, Volume rhs)
    {
        return VolumicMass::fromKgpm3(lhs.kg() / rhs.m3());
    }

    PHYSICS_CONSTEXPR Volume operator/(Mass lhs, VolumicMass rhs)
    {
        return Volume::fromM3(lhs.kg() / rhs.kgpm3());
    }

    PHYSICS_CONSTEXPR Mass operator*(Volume lhs, VolumicMass rhs)
    {
        return Mass::fromKg(lhs.m3() * rhs.kgpm3());
    }

    PHYSICS_CONSTEXPR Mass operator*(VolumicMass lhs, Volume rhs)
    {
        return rhs * lhs;
    }

}

#endif // PHYSX_OPERATORS_HPP
