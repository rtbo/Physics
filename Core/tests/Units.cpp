
#include "catch.hpp"

#include <si/AllDims.hpp>
#include <si/Constants.hpp>

#include <sstream>
#include <type_traits>

using namespace si;
using namespace si::literals;

TEST_CASE("Units", "[units]")
{
    SECTION("construction")
    {
        const auto joules = joule_t{ 12.0 };
        static_assert(
            std::is_same<decltype(joules)::dim_type, EnergyDim>::value);
        REQUIRE(joules.val() == 12.0);
    }

    SECTION("literal construction")
    {
        const auto joules = 12_J;
        static_assert(
            std::is_same<decltype(joules)::dim_type, EnergyDim>::value);
        REQUIRE(joules.val() == 12.0);
    }

    SECTION("assignment")
    {
        auto joules = joule_t{ 12.0 };
        REQUIRE(joules.val() == 12.0);

        joules = 230_J;
        REQUIRE(joules.val() == 230.0);
    }

    SECTION("comparison")
    {
        REQUIRE(1400_Pa > 1300_Pa);
        REQUIRE(1e6_J != 1400_J);
    }

    SECTION("printing")
    {
        std::ostringstream out;
        out << 1350_J_p_molK;
        REQUIRE(out.str() == u8"1350 J.mol\u207B\u00B9.K\u207B\u00B9");
    }

    SECTION("unary minus")
    {
        const auto p = 230_Pa;
        const auto pminus = -p;
        REQUIRE(-pminus == p);
        REQUIRE(pminus == pascal_t{ -230.0 });
    }

    SECTION("addition")
    {
        REQUIRE(123.4_m + 15_m == 138.4_m);
        REQUIRE(12_ohm + 14_kohm == 14012_ohm);
    }

    SECTION("subtraction")
    {
        REQUIRE(123.4_m - 15_m == 108.4_m);
        REQUIRE(12_ohm - 14_kohm == -13988_ohm);
    }

    SECTION("multiplication")
    {
        REQUIRE(2_m * 3_m == 6_m2);
        REQUIRE(2_m3 * 4_Pa == 8_J);
        REQUIRE(1200 * 4_L == 4.8_m3);
        REQUIRE(4 * 1200_L == 4.8_m3);
    }

    SECTION("division")
    {
        REQUIRE(6_m2 / 3_m == 2_m);
        REQUIRE(8_J / 4_Pa == 2_m3);
        REQUIRE(8_J / 4 == 2_J);
        REQUIRE(1 / 10_ms == 100_Hz);
    }

    SECTION("composition")
    {
        REQUIRE(240_m / 12_s == 20_m_p_s);
        REQUIRE(240_km / 12_s == 20000_m_p_s);

        REQUIRE(12_m3 * 40_hPa == 48_kJ);

        static_assert(
            std::is_same_v<PowDim<LengthDim, std::ratio<2, 1>>, AreaDim>);

        REQUIRE(square(5_m) == 25_m2);
        REQUIRE(square(1_km) == 1000000_m2);
        REQUIRE(1_h == 3600_s);
        REQUIRE((36_km / 1_h) == 10_m_p_s);
        REQUIRE((0.5 * 1000_kg * square(36_km / 1_h)) == 50_kJ);
    }

    SECTION("prefixes/conversion")
    {
        REQUIRE(1013.25_hPa == 101325_Pa);
        REQUIRE(12000_mg == 12_g);
        REQUIRE(12000_mg == 0.012_kg);
        REQUIRE(10000_g == 10_kg);

        REQUIRE(360_deg == 1_coef);
        REQUIRE(radian_t{ detail::pi } == 0.5_coef);
        REQUIRE(radian_t{ detail::pi } == 180_deg);
        REQUIRE(55_percent == 0.55_coef);
    }
}
