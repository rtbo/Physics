
#pragma once

#include "Dim.hpp"

#include <type_traits>

namespace si {

    template<typename D, typename C>
    class unit;

    template<typename D>
    class Value
    {
    private:
        double _repr;

        // friend class cannot be specialized,
        // so can't explicitely use the same D
        template<typename D_, typename C>
        friend class unit;

    public:
        using dim_type = D;

        constexpr explicit Value() :
            _repr { 0.0 }
        {}

        template<typename C>
        constexpr Value(const unit<D, C> &val) :
            _repr { C::conv(val.val()) }
        {}

        template<typename D_=D, typename =
                std::enable_if_t<std::is_same_v<D_, D> && std::is_same_v<NoDim, D> > >
        constexpr Value(const double coef) :
            _repr { coef }
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
    };

    namespace detail {
        template<typename T>
        struct is_value_helper : std::false_type {};

        template<typename D>
        struct is_value_helper<Value<D> > : std::true_type {};
    }

    template<typename V>
    constexpr bool is_value()
    {
        return detail::is_value_helper<V>::value;
    }
}
