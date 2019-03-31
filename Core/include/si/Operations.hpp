
#pragma once

#include "Dim.hpp"
#include "Value.hpp"
#include "Unit.hpp"

#include <cmath>

namespace si {



    // // mixed operations (units and value)

    template<typename D, typename C>
    inline constexpr auto
    operator==(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs == Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto
    operator==(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } == rhs;
    }

    template<typename D, typename C>
    inline constexpr auto
    operator!=(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs != Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto
    operator!=(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } != rhs;
    }

    template<typename D, typename C>
    inline constexpr auto
    operator<(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs < Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto
    operator<(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } < rhs;
    }

    template<typename D, typename C>
    inline constexpr auto
    operator>(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs > Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto
    operator>(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } > rhs;
    }

    template<typename D, typename C>
    inline constexpr auto
    operator<=(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs <= Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto
    operator<=(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } <= rhs;
    }

    template<typename D, typename C>
    inline constexpr auto
    operator>=(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs >= Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto
    operator>=(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } >= rhs;
    }

    template<typename DL, typename DR, typename C>
    inline constexpr auto
    operator*(const Value<DL> &lhs, const unit<DR, C> &rhs)
    {
        return lhs * Value<DR>{ rhs };
    }

    template<typename DL, typename DR, typename C>
    inline constexpr auto
    operator*(const unit<DL, C> &lhs, const Value<DR> &rhs)
    {
        return Value<DL>{ lhs } * rhs;
    }

    template<typename DL, typename DR, typename C>
    inline constexpr auto
    operator/(const Value<DL> &lhs, const unit<DR, C> &rhs)
    {
        return lhs / Value<DR>{ rhs };
    }

    template<typename DL, typename DR, typename C>
    inline constexpr auto
    operator/(const unit<DL, C> &lhs, const Value<DR> &rhs)
    {
        return Value<DL>{ lhs } / rhs;
    }

    template<typename D, typename C>
    inline constexpr auto
    operator+(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs + Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto
    operator+(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } + rhs;
    }

    template<typename D, typename C>
    inline constexpr auto
    operator-(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs - Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto
    operator-(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } - rhs;
    }
}
