/*
    Copyright (C) 2013-2014 Remi Thebault
    All rights reserved.

    This program and its source code are distributed under the
    terms of the BSD-style license, that can be found in the
    License.txt file at project root.
*/

#ifndef PHYSICS_PHYSICS_HPP
#define PHYSICS_PHYSICS_HPP

#include "ph/_IncludeAll.hpp"

#include "Operators.hpp"
#include "Constants.hpp"

#include "ph/Literals.hpp"


namespace std {

    // compiles with mingw, not sure this is legal
    template<class PhT>
    constexpr PhT abs (const PhT& value) {
        return (value < ph::zero) ? -value : value;
    }

}



namespace ph {

    // a few goodies

    constexpr Length circle (const Length& radius)
    {
        return 2 * pi() * radius;
    }

    constexpr Area disk (const Length& radius)
    {
        return pi() * radius * radius;
    }

    constexpr Volume sphere (const Length& radius)
    {
        return radius * radius * radius * pi() * 4.0 / 3.0;
    }


    constexpr Volume cube (const Length& side)
    {
        return side * side * side;
    }




    constexpr double density(const VolumicMass& vm) {
        return vm.kgpl();
    }




    constexpr Energy cineticEnergy(const Mass& m, const Velocity& v)
    {
        return Energy::fromJ(0.5 * m.kg() * v.mps() * v.mps());
    }


    constexpr Pressure hydrostaticPressure(const VolumicMass& rho,
                                                   const Length& h,
                                                   const Acceleration& g=Acceleration::fromG(1.0)) {
        return Pressure::fromPa(rho.kgpm3() * g.mps2() * h.m());
    }

}

#endif // PHYSICS_PHYSICS_HPP
