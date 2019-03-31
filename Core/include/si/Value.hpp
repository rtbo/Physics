
#pragma once

#include "Dim.hpp"

#include <type_traits>
#include <cmath>

namespace si {

    template<typename D, typename C>
    class unit;

    template<typename D>
    class Value
    {
    private:
        double _repr = 0.0;

        template<typename D_, typename C>
        friend class unit;

        template<typename D_>
        friend class Value;

        // private contructor for values with dimensions
        template<typename D_=D>
        constexpr explicit Value(const double repr,
                                 std::enable_if_t<
                                    std::is_same_v<D_, D> &&
                                    !std::is_same_v<NoDim, D>>* = nullptr) :
            _repr { repr }
        {}

    public:
        using dim_type = D;

        constexpr explicit Value() :
            _repr { 0.0 }
        {}

        template<typename C>
        constexpr Value(const unit<D, C> &val) :
            _repr { C::conv(val.val()) }
        {}

        // public (implicit) contructor for values without dimensions
        template<typename D_=D>
        constexpr Value(const double repr,
                        std::enable_if_t< std::is_same_v<D_, D> && std::is_same_v<NoDim, D>>* = nullptr)
            : _repr { repr }
        {}

        constexpr Value(const Value &val) = default;
        constexpr Value& operator=(const Value &val) = default;

        template<typename C>
        constexpr Value& operator=(const unit<dim_type, C> &val)
        {
            _repr = C::conv(val.val());
            return *this;
        }

        Value &operator+=(const Value &rhs)
        {
            _repr += rhs._repr;
            return *this;
        }

        Value &operator-=(const Value &rhs)
        {
            _repr -= rhs._repr;
            return *this;
        }

        Value &operator*=(const double &rhs)
        {
            _repr *= rhs;
            return *this;
        }

        Value &operator/=(const double &rhs)
        {
            _repr /= rhs;
            return *this;
        }


        template <typename D_=D, typename =
            std::enable_if_t< std::is_same_v<D, NoDim> && std::is_same_v<D_, D> > >
        operator double () const
        {
            return _repr;
        }

        template<typename Unit>
        Unit as() const {
            static_assert(std::is_same<dim_type, typename Unit::dim_type>::value);
            return Unit{ *this };
        }

    private:
        template<typename _D>
        friend constexpr bool operator==(const Value<_D> &lhs, const Value<_D> &rhs);

        template<typename _D>
        friend constexpr bool operator!=(const Value<_D> &lhs, const Value<_D> &rhs);

        template<typename _D>
        friend constexpr bool operator<(const Value<_D> &lhs, const Value<_D> &rhs);

        template<typename _D>
        friend constexpr bool operator>(const Value<_D> &lhs, const Value<_D> &rhs);

        template<typename _D>
        friend constexpr bool operator<=(const Value<_D> &lhs, const Value<_D> &rhs);

        template<typename _D>
        friend constexpr bool operator>=(const Value<_D> &lhs, const Value<_D> &rhs);

        template<typename _D>
        friend constexpr Value<_D> operator-(const Value<_D> &v);

        template<typename _D>
        friend constexpr Value<_D> operator+(const Value<_D> &lhs, const Value<_D> &rhs);

        template<typename _D>
        friend constexpr Value<_D> operator-(const Value<_D> &lhs, const Value<_D> &rhs);

        template<typename LD, typename RD>
        friend constexpr auto operator*(const Value<LD> &lhs, const Value<RD> &rhs);

        template<typename _D>
        friend constexpr Value<_D> operator*(const Value<_D> &lhs, const double &rhs);

        template<typename _D>
        friend constexpr Value<_D> operator*(const double &lhs, const Value<_D> &rhs);

        template<typename LD, typename RD>
        friend constexpr auto operator/(const Value<LD> &lhs, const Value<RD> &rhs);

        template<typename _D>
        friend constexpr Value<_D> operator/(const Value<_D> &lhs, const double &rhs);

        template<typename _D>
        friend constexpr auto operator/(const double &lhs, const Value<_D> &rhs);

        template<typename R, typename _D>
        friend constexpr auto pow(const Value<_D> &val);

    };

    namespace detail {
        template<typename T>
        struct is_value_helper : std::false_type {};

        template<typename D>
        struct is_value_helper<Value<D> > : std::true_type {};
    }

    template<typename V>
    inline constexpr bool is_value()
    {
        return detail::is_value_helper<V>::value;
    }

    template<typename D>
    inline constexpr bool operator==(const Value<D> &lhs, const Value<D> &rhs)
    {
        return lhs._repr == rhs._repr;
    }

    template<typename D>
    inline constexpr bool operator!=(const Value<D> &lhs, const Value<D> &rhs)
    {
        return lhs._repr != rhs._repr;
    }

    template<typename D>
    inline constexpr bool operator<(const Value<D> &lhs, const Value<D> &rhs)
    {
        return lhs._repr < rhs._repr;
    }

    template<typename D>
    inline constexpr bool operator>(const Value<D> &lhs, const Value<D> &rhs)
    {
        return lhs._repr > rhs._repr;
    }

    template<typename D>
    inline constexpr bool operator<=(const Value<D> &lhs, const Value<D> &rhs)
    {
        return lhs._repr <= rhs._repr;
    }

    template<typename D>
    inline constexpr bool operator>=(const Value<D> &lhs, const Value<D> &rhs)
    {
        return lhs._repr >= rhs._repr;
    }

    template<typename D>
    inline constexpr Value<D> operator-(const Value<D> &v)
    {
        return Value<D>{ -v._repr };
    }

    template<typename D>
    inline constexpr Value<D> operator+(const Value<D> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs._repr + rhs._repr };
    }

    template<typename D>
    inline constexpr Value<D> operator-(const Value<D> &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs._repr - rhs._repr };
    }

    template<typename LD, typename RD>
    inline constexpr auto operator*(const Value<LD> &lhs, const Value<RD> &rhs)
    {
        return Value<MulDim<LD, RD>>{ lhs._repr * rhs._repr };
    }

    template<typename D>
    inline constexpr Value<D> operator*(const Value<D> &lhs, const double &rhs)
    {
        return Value<D>{ lhs._repr * rhs };
    }

    template<typename D>
    inline constexpr Value<D> operator*(const double &lhs, const Value<D> &rhs)
    {
        return Value<D>{ lhs * rhs._repr };
    }

    template<typename LD, typename RD>
    inline constexpr auto operator/(const Value<LD> &lhs, const Value<RD> &rhs)
    {
        return Value<DivDim<LD, RD>>{ lhs._repr / rhs._repr };
    }

    template<typename D>
    inline constexpr Value<D> operator/(const Value<D> &lhs, const double &rhs)
    {
        return Value<D>{ lhs._repr / rhs };
    }

    template<typename D>
    inline constexpr auto operator/(const double &lhs, const Value<D> &rhs)
    {
        return Value<DivDim<NoDim, D>>{ lhs / rhs._repr };
    }

    template<typename R, typename D>
    inline constexpr auto pow(const Value<D> &val)
    {
        using dim = PowDim<D, R>;
        return Value<dim> {
            std::pow(val._repr, detail::ratio_double<R>())
        };
    }

    template<typename D>
    inline constexpr auto square(const Value<D> &val)
    {
        return pow<std::ratio<2, 1>>(val);
    }

    template<typename D>
    inline constexpr auto cube(const Value<D> &val)
    {
        return pow<std::ratio<3, 1>>(val);
    }

    template<typename D>
    inline constexpr auto sqrt(const Value<D> &val)
    {
        return pow<std::ratio<1, 2>>(val);
    }

    template<typename D>
    inline constexpr auto cbrt(const Value<D> &val)
    {
        return pow<std::ratio<1, 3>>(val);
    }

    template<typename D>
    inline constexpr Value<D> abs(const Value<D> &v)
    {
        return v < Value<D>{} ? -v : v;
    }

    template<typename D>
    inline constexpr Value<D> min(const Value<D> &v1, const Value<D> &v2)
    {
        return v1 < v2 ? v1 : v2;
    }

    template<typename D>
    inline constexpr Value<D> max(const Value<D> &v1, const Value<D> &v2)
    {
        return v1 > v2 ? v1 : v2;
    }

    template<typename D>
    inline constexpr Value<D> clamp(const Value<D> &val, const Value<D> &minVal, const Value<D> &maxVal)
    {
        return max(min(val, maxVal), minVal);
    }
}
