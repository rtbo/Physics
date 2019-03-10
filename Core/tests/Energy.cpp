
#include <si/Units.hpp>
#include "catch.hpp"
#include <type_traits>

using namespace si;

TEST_CASE("Energy", "[energy]")
{

    SECTION("construction") {

        auto joules = Mass{1.0} * Velocity{1.0} * Velocity{1.0};

        static_assert(std::is_same<decltype(joules), Value<EnergyDimSet>>::value);
        static_assert(std::is_same<decltype(joules), Energy>::value);
    }

}
