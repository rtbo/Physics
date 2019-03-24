
#pragma once

#include "Dim.hpp"

#include <type_traits>

namespace si {

    template<typename D, typename Conv>
    class unit;

    template<typename D>
    class Value
    {
    private:
        double _repr;

        // friend class cannot be specialized,
        // so can't explicitely use the same D
        template<typename D_, typename Conv>
        friend class unit;

    public:
        using dim_type = D;

        constexpr explicit Value() :
            _repr { 0.0 }
        {}

        template<typename Unit>
        constexpr Value(const Unit &val) :
            _repr {Unit::conv_type::conv(val.val())}
        {
            static_assert(std::is_same<dim_type, typename Unit::dim_type>::value);
        }

        constexpr Value(const Value &val) = default;
        constexpr Value& operator=(const Value &val) = default;

        template<typename Unit>
        constexpr Value& operator=(const Unit &val)
        {
            static_assert(std::is_same<dim_type, typename Unit::dim_type>::value);
            _repr = Unit::conv_type::conv(val.val());
            return *this;
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
