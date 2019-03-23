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

        constexpr explicit unit(const double val) :
            _val{val}
        {}

        constexpr unit(const Value<D> &val) :
            _val { C::reverse_conv(val._repr) }
        {}

        constexpr unit(const unit &val) = default;
        constexpr unit& operator=(const unit &val) = default;

        constexpr double val() const
        {
            return _val;
        }

        constexpr double repr() const
        {
            return C::conv(_val);
        }
    };

    namespace detail {
        template<typename T>
        struct is_unit_helper : std::false_type {};

        template<typename D, typename Conv>
        struct is_unit_helper<unit<D, Conv> > : std::true_type {};

        template<typename T>
        struct default_unit_helper
        {};

        template<typename D>
        struct default_unit_helper<Value<D> >
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
        return value.template as<default_unit<V>>();
    }
}

