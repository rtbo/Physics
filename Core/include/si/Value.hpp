
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

        template<typename unit>
        constexpr Value(const unit &val) :
            _repr {unit::conv_type::conv(val.val())}
        {
            static_assert(std::is_same<dim_type, typename unit::dim_type>::value);
        }

        constexpr Value(const Value &val) = default;
        constexpr Value& operator=(const Value &val) = default;

        template<typename unit>
        constexpr Value& operator=(const unit &val)
        {
            static_assert(std::is_same<dim_type, typename unit::dim_type>::value);
            _repr = unit::conv_type::conv(val.val());
            return *this;
        }

        template<typename unit>
        unit as() const {
            static_assert(std::is_same<dim_type, typename unit::dim_type>::value);
            unit{ *this };
        }
    };
}
