#include "catch.hpp"

#include <si/AllDims.hpp>

using namespace si::literals;
using namespace si;

TEST_CASE("Conversions", "[conversion]")
{
    SECTION("length") { REQUIRE(millimeter(0.012_m) == 12); }

    SECTION("pressure")
    {
        REQUIRE(millibar(140_hPa) == 140);
        REQUIRE(hectopascal(145_hPa) == 145);
        REQUIRE(hectopascal(145_kPa) == 1450);
        REQUIRE(bar(145_kPa) == 1.45);
        REQUIRE(torr(1_atm) == 760);
    }
}
