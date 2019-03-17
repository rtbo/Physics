
#include <si/Energy.hpp>
#include <si/Mass.hpp>
#include <si/Velocity.hpp>
#include <si/Operations.hpp>
#include <si/Constants.hpp>
#include "catch.hpp"
#include <type_traits>

using namespace si;
using namespace si::literals;

TEST_CASE("Units", "[units]")
{

    SECTION("construction") {

        auto joules = joule_t{12.0};
        auto energy = Energy{joules};

        static_assert(std::is_same<decltype(joules)::dim_type, EnergyDim>::value);
    }

    SECTION("conversion") {

        auto kgs = 10_kg;
        auto gs = 10000_g;

        REQUIRE(Mass{gs} == Mass{kgs});
    }

}
