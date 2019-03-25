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

    namespace detail {

        template<typename LC, typename RC>
        struct MulConvHelper
        {};

        template<typename LF, int LP, typename RF, int RP>
        struct MulConvHelper<factor_piexp_conv<LF, LP>, factor_piexp_conv<RF, RP>>
        {
            using type = factor_piexp_conv<std::ratio_multiply<LF, RF>, LP+RP>;
        };

        template<typename LC, typename RC>
        struct DivConvHelper
        {};

        template<typename LF, int LP, typename RF, int RP>
        struct DivConvHelper<factor_piexp_conv<LF, LP>, factor_piexp_conv<RF, RP>>
        {
            using type = factor_piexp_conv<std::ratio_divide<LF, RF>, LP-RP>;
        };

        constexpr intmax_t ipow(intmax_t base, intmax_t exp, intmax_t result = 1)
        {
            return exp < 1 ? result : ipow(base*base, exp/2, (exp % 2) ? result*base : result);
        }

        template<typename C, int Exp>
        struct PowConvHelper
        {};

        template<intmax_t FN, intmax_t FD, intmax_t P, intmax_t Exp>
        struct PowConvHelper<factor_piexp_conv<::std::ratio<FN, FD>, P>, Exp>
        {
            using type = factor_piexp_conv<std::ratio<ipow(FN, Exp), ipow(FD, Exp)>, P*Exp>;
        };

    }

    template<typename Lhs, typename Rhs>
    using MulConv = typename detail::MulConvHelper<Lhs, Rhs>::type;

    template<typename Lhs, typename Rhs>
    using DivConv = typename detail::DivConvHelper<Lhs, Rhs>::type;

    template<typename C, int Exp>
    using PowConv = typename detail::PowConvHelper<C, Exp>::type;
}
