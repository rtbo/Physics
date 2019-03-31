#pragma once

#include <ratio>
#include <cmath>

namespace si {

    namespace detail {
        constexpr double pi = 3.14159265358979323846;

        template<int PiExp>
        struct pow_pi
        {};

        template<>
        struct pow_pi<-3>
        {
            static constexpr double value = 1.0 / (pi*pi*pi);
        };
        template<>
        struct pow_pi<-2>
        {
            static constexpr double value = 1.0 / (pi*pi);
        };
        template<>
        struct pow_pi<-1>
        {
            static constexpr double value = 1.0 / pi;
        };

        template<>
        struct pow_pi<0>
        {
            static constexpr double value = 1.0;
        };

        template<>
        struct pow_pi<1>
        {
            static constexpr double value = pi;
        };
        template<>
        struct pow_pi<2>
        {
            static constexpr double value = pi*pi;
        };
        template<>
        struct pow_pi<3>
        {
            static constexpr double value = pi*pi*pi;
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
            return (val + detail::ratio_double<OR>())
                * detail::ratio_double<FR>()
                * detail::pow_pi<PiExp>::value;
        }

        static constexpr double reverse_conv(double val)
        {
            return (val / (detail::ratio_double<FR>() * detail::pow_pi<PiExp>::value))
                - detail::ratio_double<OR>();
        }
    };

    using identity_conv = conversion<std::ratio<1>, std::ratio<0>, 0>;

    template<typename FR>
    using factor_conv = conversion<FR, std::ratio<0>, 0>;

    template<int PiExp>
    using piexp_conv = conversion<std::ratio<1>, std::ratio<0>, PiExp>;

    template<typename FR, int PiExp>
    using factor_piexp_conv = conversion<FR, std::ratio<0>, PiExp>;

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
}
