#pragma once

#include "Dim.hpp"
#include "Value.hpp"

#include <type_traits>
#include <cmath>

namespace si {

    namespace detail {
        template<int PiExp>
        struct pow_pi
        {};

        template<>
        struct pow_pi<-1>
        {
            static constexpr double value = 1.0 / M_PI;
        };

        template<>
        struct pow_pi<0>
        {
            static constexpr double value = 1.0;
        };

        template<>
        struct pow_pi<1>
        {
            static constexpr double value = M_PI;
        };
    }

    template<typename FR=std::ratio<1>, typename OR=std::ratio<0>, int PiExp=0>
    struct conversion
    {
        static_assert(detail::is_ratio<FR>(), "conversion must be used with std::ratio");
        static_assert(detail::is_ratio<OR>(), "conversion must be used with std::ratio");

        using factor = FR;
        using offset = OR;
        static constexpr int pi_exp = PiExp;

        static constexpr double conv(double val)
        {
            return val
                * detail::ratio_double<FR>()
                * detail::pow_pi<PiExp>::value
                + detail::ratio_double<OR>();
        }

        static constexpr double reverse_conv(double val)
        {
            return (val - detail::ratio_double<OR>()) /
                (detail::ratio_double<FR>() * detail::pow_pi<PiExp>::value);
        }
    };

    using identity_conv = conversion<std::ratio<1>, std::ratio<0>, 0>;

    template<typename FR>
    using factor_conv = conversion<FR, std::ratio<0>, 0>;

    template<typename FR, typename OR>
    using factor_offset_conv = conversion<FR, OR, 0>;

    namespace detail {
        template<typename T>
        struct is_conv_helper : std::false_type {};

        template<typename FR, typename OR, int PiExp>
        struct is_conv_helper<conversion<FR, OR, PiExp> > : std::true_type {};
    }

    template<typename Conv>
    constexpr bool is_conv()
    {
        return detail::is_conv_helper<Conv>::value;
    }

    template<typename D, typename Conv>
    class unit
    {
    private:

        static_assert(is_dim<D>());
        static_assert(is_conv<Conv>());

        double _val;

    public:

        using dim_type = D;
        using conv_type = Conv;
        using value_type = Value<D>;

        constexpr explicit unit(const double val) :
            _val{val}
        {}

        constexpr unit(const Value<D> &val) :
            _val { Conv::reverse_conv(val._repr) }
        {}

        constexpr unit(const unit &val) = default;
        constexpr unit& operator=(const unit &val) = default;

        constexpr double val() const
        {
            return _val;
        }

        constexpr double repr() const
        {
            return Conv::conv(_val);
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

