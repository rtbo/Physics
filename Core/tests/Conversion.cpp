#include <si/AllDims.hpp>
#include "catch.hpp"

using namespace si::literals;
using namespace si;

TEST_CASE("Conversions", "[conversion]")
{
    REQUIRE( millimeter( 0.012_m ) == 12 );
    REQUIRE( hectopascal( 145_hPa ) == 145 );
    REQUIRE( hectopascal( 145_kPa ) == 1450 );
    REQUIRE( bar( 145_kPa ) == 1.45 );
    REQUIRE( torr( 1_atm ) == 760 );
}
