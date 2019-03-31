#pragma once

#include "Conversion.hpp"
#include "Dim.hpp"
#include "Value.hpp"

#include <type_traits>

namespace si {
    template<typename D, typename C>
    class unit
    {
    private:

        static_assert(is_dim<D>());
        static_assert(is_conv<C>());

        double _val;

    public:

        using dim_type = D;
        using conv_type = C;
        using value_type = Value<D>;

        constexpr explicit unit() :
            _val{ 0.0 }
        {}

        constexpr explicit unit(const double val) :
            _val{ val }
        {}

        constexpr unit(const Value<D> &val) :
            _val { C::reverse_conv(val._repr) }
        {}

        constexpr unit(const unit &val) = default;
        constexpr unit& operator=(const unit &val) = default;

        constexpr explicit operator double() const
        {
            return _val;
        }

        constexpr operator Value<dim_type>() const
        {
            return Value<dim_type>{ *this };
        }

        constexpr double val() const
        {
            return _val;
        }

        constexpr double repr() const
        {
            return C::conv(_val);
        }
    };

    template<typename D, typename C>
    constexpr Value<D> value(const unit<D, C> &u)
    {
        return Value<D>{ u };
    }

    namespace detail {
        template<typename T>
        struct is_unit_helper : std::false_type {};

        template<typename D, typename Conv>
        struct is_unit_helper<unit<D, Conv> > : std::true_type {};

        template<typename T>
        struct default_unit_helper
        {};

        template<typename D>
        struct default_unit_helper<Value<D>>
        {
            using type = unit<D, identity_conv>;
        };
    }

    template<typename Unit>
    constexpr bool is_unit()
    {
        return detail::is_unit_helper<Unit>::value;
    }

    template<typename Unit>
    constexpr bool is_unit(const Unit &)
    {
        return detail::is_unit_helper<Unit>::value;
    }

    template<typename U1, typename U2>
    constexpr bool are_units()
    {
        return is_unit<U1>() && is_unit<U2>();
    }

    template<typename U1, typename U2>
    constexpr
    std::enable_if_t<are_units<U1, U2>(), bool>
    are_compatible_units()
    {
        return std::is_same_v<typename U1::dim_type, typename U2::dim_type>;
    }

    template<typename V>
    using default_unit = typename detail::default_unit_helper<V>::type;

    template<typename V>
    constexpr default_unit<V> value_repr(const V& value)
    {
        return default_unit<V>{ value };
    }

    template<typename D, typename CL, typename CR>
    inline constexpr bool operator==(const unit<D, CL> &lhs, const unit<D, CR> &rhs)
    {
        return Value<D>{ lhs } == Value<D>{ rhs };
    }

    template<typename D, typename CL, typename CR>
    inline constexpr bool operator!=(const unit<D, CL> &lhs, const unit<D, CR> &rhs)
    {
        return Value<D>{ lhs } != Value<D>{ rhs };
    }

    template<typename D, typename CL, typename CR>
    inline constexpr bool operator<=(const unit<D, CL> &lhs, const unit<D, CR> &rhs)
    {
        return Value<D>{ lhs } <= Value<D>{ rhs };
    }

    template<typename D, typename CL, typename CR>
    inline constexpr bool operator>=(const unit<D, CL> &lhs, const unit<D, CR> &rhs)
    {
        return Value<D>{ lhs } >= Value<D>{ rhs };
    }

    template<typename D, typename CL, typename CR>
    inline constexpr bool operator<(const unit<D, CL> &lhs, const unit<D, CR> &rhs)
    {
        return Value<D>{ lhs } < Value<D>{ rhs };
    }

    template<typename D, typename CL, typename CR>
    inline constexpr bool operator>(const unit<D, CL> &lhs, const unit<D, CR> &rhs)
    {
        return Value<D>{ lhs } > Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator-(const unit<D, C> &u)
    {
        return unit<D, C>{ -u.val() };
    }

    template<typename LD, typename LC, typename RD, typename RC>
    inline constexpr auto operator*(const unit<LD, LC> &lhs, const unit<RD, RC> &rhs)
    {
        return Value<LD>{ lhs } * Value<RD>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator*(const double &lhs, const unit<D, C> &rhs)
    {
        return lhs * Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator*(const unit<D, C> &lhs, const double &rhs)
    {
        return Value<D>{ lhs } * rhs;
    }

    // div
    template<typename LD, typename LC, typename RD, typename RC>
    inline constexpr auto operator/(const unit<LD, LC> &lhs, const unit<RD, RC> &rhs)
    {
        return Value<LD>{ lhs } / Value<RD>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator/(const double &lhs, const unit<D, C> &rhs)
    {
        return lhs / Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator/(const unit<D, C> &lhs, const double &rhs)
    {
        return Value<D>{ lhs } / rhs;
    }

    template<typename D, typename C>
    inline constexpr auto operator+(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return Value<D>{ lhs } + Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr unit<D, C> operator-(const unit<D, C> &lhs, const unit<D, C> &rhs)
    {
        return Value<D>{ lhs } - Value<D>{ rhs };
    }

    template<typename R, typename D, typename C>
    inline constexpr auto pow(const unit<D, C> &val)
    {
        return pow(Value<D>{ val });
    }

    template<typename D, typename C>
    inline constexpr auto square(const unit<D, C> &val)
    {
        return pow<std::ratio<2, 1>>(Value<D>{ val });
    }

    template<typename D, typename C>
    inline constexpr auto cube(const unit<D, C> &val)
    {
        return pow<std::ratio<3, 1>>(Value<D>{ val });
    }

    template<typename D, typename C>
    inline constexpr auto sqrt(const unit<D, C> &val)
    {
        return pow<std::ratio<1, 2>>(Value<D>{ val });
    }

    template<typename D, typename C>
    inline constexpr auto cbrt(const unit<D, C> &val)
    {
        return pow<std::ratio<1, 3>>(Value<D>{ val });
    }


    template<typename D, typename C>
    inline constexpr unit<D, C> abs(const unit<D, C> &v)
    {
        return v < unit<D, C>{} ? -v : v;
    }

    template<typename D, typename C>
    inline constexpr unit<D, C> min(const unit<D, C> &v1, const unit<D, C> &v2)
    {
        return v1 < v2 ? v1 : v2;
    }

    template<typename D, typename C>
    inline constexpr unit<D, C> max(const unit<D, C> &v1, const unit<D, C> &v2)
    {
        return v1 > v2 ? v1 : v2;
    }

    template<typename D, typename C>
    inline constexpr unit<D, C> clamp(const unit<D, C> &u, const unit<D, C> &umin, const unit<D, C> &umax)
    {
        return max(min(u, umax), umin);
    }

    // mixed operations (units and value)

    template<typename D, typename C>
    inline constexpr auto operator==(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs == Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator==(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } == rhs;
    }

    template<typename D, typename C>
    inline constexpr auto operator!=(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs != Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator!=(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } != rhs;
    }

    template<typename D, typename C>
    inline constexpr auto operator<(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs < Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator<(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } < rhs;
    }

    template<typename D, typename C>
    inline constexpr auto operator>(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs > Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator>(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } > rhs;
    }

    template<typename D, typename C>
    inline constexpr auto operator<=(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs <= Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator<=(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } <= rhs;
    }

    template<typename D, typename C>
    inline constexpr auto operator>=(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs >= Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator>=(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } >= rhs;
    }

    template<typename DL, typename DR, typename C>
    inline constexpr auto operator*(const Value<DL> &lhs, const unit<DR, C> &rhs)
    {
        return lhs * Value<DR>{ rhs };
    }

    template<typename DL, typename DR, typename C>
    inline constexpr auto operator*(const unit<DL, C> &lhs, const Value<DR> &rhs)
    {
        return Value<DL>{ lhs } * rhs;
    }

    template<typename DL, typename DR, typename C>
    inline constexpr auto operator/(const Value<DL> &lhs, const unit<DR, C> &rhs)
    {
        return lhs / Value<DR>{ rhs };
    }

    template<typename DL, typename DR, typename C>
    inline constexpr auto operator/(const unit<DL, C> &lhs, const Value<DR> &rhs)
    {
        return Value<DL>{ lhs } / rhs;
    }

    template<typename D, typename C>
    inline constexpr auto operator+(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs + Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator+(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } + rhs;
    }

    template<typename D, typename C>
    inline constexpr auto operator-(const Value<D> &lhs, const unit<D, C> &rhs)
    {
        return lhs - Value<D>{ rhs };
    }

    template<typename D, typename C>
    inline constexpr auto operator-(const unit<D, C> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs } - rhs;
    }
}
