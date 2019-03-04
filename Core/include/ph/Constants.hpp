/*
    Copyright (C) 2013-2014 Remi Thebault
    All rights reserved.

    This program and its source code are distributed under the
    terms of the BSD-style license, that can be found in the
    License.txt file at project root.
*/

#ifndef PHYSICS_CONSTANTS_HPP
#define PHYSICS_CONSTANTS_HPP


namespace ph {



    constexpr double R()
    {
        return 8.3144621;
    }


    // mathematical constants


    constexpr double pi()
    {
        return 3.14159265358979323846;
    }

    constexpr double twoPi()
    {
        return 2.0 * pi();
    }

    constexpr double piOver2()
    {
        return pi() / 2.0;
    }

    constexpr double piOver4()
    {
        return pi() / 4.0;
    }

    constexpr double oneOverPi()
    {
        return 1.0 / pi();
    }

    constexpr double twoOverPi()
    {
        return 2.0 / pi();
    }



    constexpr double twoOverSqrtPi()
    {
        return 1.12837916709551257390;
    }

    constexpr double sqrt2()
    {
        return 1.41421356237309504880;
    }

    constexpr double sqrt1Over2()
    {
        return 0.70710678118654752440;
    }




    constexpr double e()
    {
        return 2.7182818284590452354;
    }


    constexpr double log2e()
    {
        return 1.4426950408889634074;
    }

    constexpr double log10e()
    {
        return 0.43429448190325182765;
    }

    constexpr double ln2()
    {
        return 0.69314718055994530942;
    }

    constexpr double ln10()
    {
        return 2.30258509299404568402;
    }
}

#endif // PHYSX_CONSTANTS_HPP
