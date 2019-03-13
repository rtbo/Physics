
#include <si/Energy.hpp>
#include <si/Mass.hpp>
#include <si/Velocity.hpp>
#include <si/Operations.hpp>
#include "catch.hpp"
#include <type_traits>

using namespace si;

TEST_CASE("Energy", "[energy]")
{

    SECTION("construction") {

        auto joules = joule_t{12.0};
        auto energy = Energy{joules};

        static_assert(std::is_same<decltype(joules)::dim_type, EnergyDim>::value);
        //static_assert(std::is_same<decltype(joules), Energy>::value);
    }

}
