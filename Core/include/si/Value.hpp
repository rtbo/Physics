
#pragma once

namespace si {

    class ValueBase
    {
    private:
        double _val;

    public:

        constexpr explicit ValueBase(const double val) :
            _val{val}
        {}

        constexpr ValueBase(const ValueBase &val) = default;
        constexpr ValueBase& operator=(const ValueBase &val) = default;

        constexpr double val() const
        {
            return _val;
        }
    };

    template<typename DS>
    class Value : public ValueBase
    {
    public:
        using dim_set = DS;

        constexpr explicit Value(const double val) :
            ValueBase{val}
        {}

        constexpr Value(const Value &val) = default;
        constexpr Value& operator=(const Value &val) = default;
    };
}
