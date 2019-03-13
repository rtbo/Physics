#pragma once

#include "Dim.hpp"
#include "Value.hpp"

namespace si {

    template<typename R>
    struct factor_conv
    {
        static_assert(detail::is_ratio<R>(), "factor_conv must be used with std::ratio");
        using factor = R;

        static constexpr double conv(double val)
        {
            return val * detail::ratio_double<factor>();
        }

        static constexpr double reverse_conv(double val)
        {
            return val / detail::ratio_double<factor>();
        }
    };

    template<typename FR, typename OR>
    struct factor_offset_conv
    {
        static_assert(detail::is_ratio<FR>(), "factor_offset_conv must be used with std::ratio");
        static_assert(detail::is_ratio<OR>(), "factor_offset_conv must be used with std::ratio");

        using factor = FR;
        using offset = OR;

        static constexpr double conv(double val)
        {
            return (val + detail::ratio_double<offset>()) * detail::ratio_double<factor>();
        }

        static constexpr double reverse_conv(double val)
        {
            return (val / detail::ratio_double<factor>()) - detail::ratio_double<offset>();
        }
    };

    namespace detail {
        template<typename T>
        struct is_conv_helper : std::false_type {};

        template<typename FR>
        struct is_conv_helper<factor_conv<FR> > : std::true_type {};

        template<typename FR, typename OR>
        struct is_conv_helper<factor_offset_conv<FR, OR> > : std::true_type {};
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

        static_assert(is_dim<D>() && is_conv<Conv>());

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
    };

}
