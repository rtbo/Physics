#pragma once

#include "si/Coefficient.hpp"

#include <cmath>

namespace si {

inline Coefficient sin(const PlaneAngle &angle)
{
    return coef_t{ std::sin(radian(angle)) };
}

inline Coefficient cos(const PlaneAngle &angle)
{
    return coef_t{ std::cos(radian(angle)) };
}

inline Coefficient tan(const PlaneAngle &angle)
{
    return coef_t{ std::tan(radian(angle)) };
}

namespace consts {
    constexpr radian_t pi = radian_t{ 3.14159265358979323846 };
} // namespace consts

namespace literals {
    constexpr radian_t operator"" _pi(const long double val)
    {
        return val * ::si::consts::pi;
    }
    constexpr radian_t operator"" _pi(const unsigned long long val)
    {
        return val * ::si::consts::pi;
    }

    constexpr PlaneAngle operator"" _pi_val(const long double val)
    {
        return PlaneAngle{ val * ::si::consts::pi };
    }
    constexpr PlaneAngle operator"" _pi_val(const unsigned long long val)
    {
        return PlaneAngle{ val * ::si::consts::pi };
    }
} // namespace literals

} // namespace si
