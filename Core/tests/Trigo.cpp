
#include "catch.hpp"

#include <si/Trigo.hpp>

using namespace si::literals;

TEST_CASE("Trigo", "[coef][angle][trigo]")
{
    SECTION("conversion")
    {
        REQUIRE(360_deg == 1_coef);
        REQUIRE(si::consts::pi == 0.5_coef);
        REQUIRE(2_pi == 360_deg);
        REQUIRE(55_percent == 0.55_coef);
    }

    SECTION("functions")
    {
        REQUIRE(Approx(static_cast<double>(si::sin(0_pi))) == 0_coef);
        REQUIRE(Approx(static_cast<double>(si::sin(0.5_pi))) == 1_coef);
        REQUIRE(Approx(static_cast<double>(si::cos(0_pi))) == 1.0);
        REQUIRE(Approx(static_cast<double>(si::cos(0.5_pi))).margin(0.001) ==
                0.0);
        REQUIRE(Approx(static_cast<double>(si::cos(1_pi))) == -1.0);
        REQUIRE(Approx(static_cast<double>(si::tan(0_pi))).margin(0.001) ==
                0_coef);
        REQUIRE(Approx(static_cast<double>(si::tan(si::consts::pi)))
                    .margin(0.001) == 0_coef);
    }
}
