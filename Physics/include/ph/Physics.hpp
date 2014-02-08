/*
    Copyright (C) 2013-2014 Remi Thebault
    All rights reserved.

    This program and its source code are distributed under the
    terms of the BSD-style license, that can be found in the
    License.txt file at project root.
*/

#ifndef PHYSX_PHYSX_HPP
#define PHYSX_PHYSX_HPP

#include "Config.hpp"

#include "_IncludeAll.hpp"

#include "Operators.hpp"
#include "Constants.hpp"

#ifndef PHYSICS_NO_LITERALS
#include "Literals.hpp"
#endif


namespace std {

    // compiles with mingw, not sure this is legal
    template<class PhT>
    PHYSICS_CONSTEXPR PhT abs (const PhT& value) {
        return (value < ph::zero) ? -value : value;
    }

}



namespace ph {

    // a few goodies

    PHYSICS_CONSTEXPR Length circle (const Length& radius)
    {
        return 2 * pi() * radius;
    }

    PHYSICS_CONSTEXPR Area disk (const Length& radius)
    {
        return pi() * radius * radius;
    }

    PHYSICS_CONSTEXPR Volume sphere (const Length& radius)
    {
        return radius * radius * radius * pi() * 4.0 / 3.0;
    }


    PHYSICS_CONSTEXPR Volume cube (const Length& side)
    {
        return side * side * side;
    }




    PHYSICS_CONSTEXPR double density(const VolumicMass& vm) {
        return vm.kgpl();
    }




    PHYSICS_CONSTEXPR Energy cineticEnergy(const Mass& m, const Velocity& v)
    {
        return Energy::fromJ(0.5 * m.kg() * v.mps() * v.mps());
    }


    PHYSICS_CONSTEXPR Pressure hydrostaticPressure(const VolumicMass& rho,
                                                   const Length& h,
                                                   const Acceleration& g=Acceleration::fromG(1.0)) {
        return Pressure::fromPa(rho.kgpm3() * g.mps2() * h.m());
    }

}

#endif // PHYSX_PHYSX_HPP
