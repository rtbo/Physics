
#include <si/Area.hpp>
#include <si/Coefficient.hpp>
#include <si/ElectricResistance.hpp>
#include <si/Energy.hpp>
#include <si/Length.hpp>
#include <si/Mass.hpp>
#include <si/MolarEntropy.hpp>
#include <si/Pressure.hpp>
#include <si/Time.hpp>
#include <si/Velocity.hpp>
#include <si/Volume.hpp>
#include <si/Operations.hpp>
#include <si/Constants.hpp>

#include "catch.hpp"

#include <sstream>
#include <type_traits>

using namespace si;
using namespace si::literals;

TEST_CASE("Units", "[units]")
{

    SECTION("construction") {
        const auto joules = joule_t{12.0};
        static_assert(std::is_same<decltype(joules)::dim_type, EnergyDim>::value);
        REQUIRE(joules.val() == 12.0);
    }

    SECTION("literal construction") {
        const auto joules = 12_J;
        static_assert(std::is_same<decltype(joules)::dim_type, EnergyDim>::value);
        REQUIRE(joules.val() == 12.0);
    }

    SECTION("assignment") {
        auto joules = joule_t{12.0};
        REQUIRE(joules.val() == 12.0);

        joules = 230_J;
        REQUIRE(joules.val() == 230.0);
    }

    SECTION("composition") {
        REQUIRE( 240_m / 12_s == 20_m_p_s );
        REQUIRE( 240_km / 12_s == 20000_m_p_s );

        REQUIRE( 12_m3 * 40_hPa == 48_kJ );

        //PowDim<LengthDim, 2, 1> val = "";
        static_assert( std::is_same_v<PowDim<LengthDim, 2, 1>, AreaDim> );
        static_assert( std::is_same_v<PowConv<identity_conv, 2>, identity_conv> );
        //static_assert( std::is_same_v<PowConv<factor_conv<std::ratio<10, 36>>, 2>)

        REQUIRE( square(5_m) == 25_m2 );
        REQUIRE( square(1_km) == 1000000_m2 );
        REQUIRE( 1_h == 3600_s );
        REQUIRE( (36_km / 1_h).repr() == 10.0 );
        REQUIRE( square(36_km / 1_h).repr() == 100.0 );
        REQUIRE( (0.5 * 1000_kg * square(36_km / 1_h)).repr() == 50_kJ.repr() );
    }

    SECTION("prefixes/conversion") {
        REQUIRE( 1013.25_hPa == 101325_Pa );
        REQUIRE( 12000_mg == 12_g );
        REQUIRE( 12000_mg == 0.012_kg );
        REQUIRE( 10000_g == 10_kg );

        REQUIRE( 360_deg == 1_coef );
        REQUIRE( radian_t{ detail::pi } == 0.5_coef );
        REQUIRE( radian_t{ detail::pi } == 180_deg );
        REQUIRE( 55_percent == 0.55_coef );
    }

    SECTION("comparison") {
        REQUIRE( 1400_Pa > 1300_Pa );
        REQUIRE( 1000_ohm < 1400_ohm );
        REQUIRE( 1e6_J != 1400_J );
    }

    SECTION("printing") {
        std::ostringstream out;
        out << 1350_J_p_molK;
        REQUIRE(out.str() == u8"1350 J.mol\u207B\u00B9.K\u207B\u00B9");
    }

    SECTION("unary minus") {
        const auto p = 230_Pa;
        const auto pminus = -p;
        REQUIRE(-pminus == p);
        REQUIRE(pminus == pascal_t{-230.0});
    }
}

