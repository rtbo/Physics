#pragma once

#include <si/Config.hpp>
#include <si/Constants.hpp>

#ifdef HAVE_ACCELERATION_HPP
#    include <si/Acceleration.hpp>
#endif
#ifdef HAVE_AREA_HPP
#    include <si/Area.hpp>
#endif
#ifdef HAVE_DENSITY_HPP
#    include <si/Density.hpp>
#endif
#ifdef HAVE_ENERGY_HPP
#    include <si/Energy.hpp>
#endif
#ifdef HAVE_LENGTH_HPP
#    include <si/Length.hpp>
#endif
#ifdef HAVE_MASS_HPP
#    include <si/Mass.hpp>
#endif
#ifdef HAVE_PRESSURE_HPP
#    include <si/Pressure.hpp>
#endif
#ifdef HAVE_VELOCITY_HPP
#    include <si/Velocity.hpp>
#endif
#ifdef HAVE_VOLUME_HPP
#    include <si/Volume.hpp>
#endif

namespace si {

#ifdef HAVE_LENGTH_HPP
constexpr Length circle(const Length &radius)
{
    return 2 * detail::pi * radius;
}

#    ifdef HAVE_AREA_HPP
constexpr Area disk(const Length &radius)
{
    return detail::pi * radius * radius;
}
#    endif

#    ifdef HAVE_VOLUME_HPP
constexpr Volume sphere(const Length &radius)
{
    return radius * radius * radius * detail::pi * 4.0 / 3.0;
}

constexpr Volume cube(const Length &side)
{
    return side * side * side;
}
#    endif
#endif

#if defined(HAVE_ENERGY_HPP) && defined(HAVE_MASS_HPP) &&                      \
    defined(HAVE_VELOCITY_HPP)
constexpr Energy potentialEnergy(const Mass &m, const Length &h,
                                 const Acceleration &g = earth_gravity_t{ 1.0 })
{
    return m * g * h;
}
#endif

#if defined(HAVE_ENERGY_HPP) && defined(HAVE_MASS_HPP) &&                      \
    defined(HAVE_VELOCITY_HPP)
constexpr Energy kineticEnergy(const Mass &m, const Velocity &v)
{
    return 0.5 * m * v * v;
}
#endif

#if defined(HAVE_ACCELERATION_HPP) && defined(HAVE_DENSITY_HPP) &&             \
    defined(HAVE_LENGTH_HPP) && defined(HAVE_PRESSURE_HPP)
constexpr Pressure hydrostaticPressure(const Density &rho, const Length &h,
                                       const Acceleration &g = earth_gravity_t{
                                           1.0 })
{
    return rho * g * h;
}
#endif
} // namespace si
