/*
    Copyright (C) 2013-2019 Remi Thebault
    All rights reserved.

    This program and its source code are distributed under the
    terms of the BSD-style license, that can be found in the
    License.txt file at project root.
*/

#include "catch.hpp"

#include <si/Action.hpp>
#include <si/Area.hpp>
#include <si/Energy.hpp>
#include <si/Length.hpp>
#include <si/SpecificHeatCapacity.hpp>
#include <si/Volume.hpp>
#include <si/VolumetricFlowRate.hpp>

#include <sstream>

using namespace si::literals;

template<typename T>
std::string ostr(const T &value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// std::string ustr(const char16_t *str)
// {

// }

TEST_CASE("Output", "[output]")
{
    SECTION("simple unit output")
    {
        REQUIRE(ostr(3_m) == "3 m");
        REQUIRE(ostr(3.32_m) == "3.32 m");
        REQUIRE(ostr(12_J) == "12 J");
        REQUIRE(ostr(18.4_J) == "18.4 J");
    }

    SECTION("compound unit output")
    {
        REQUIRE(ostr(45_Js) == "45 J.s");
        REQUIRE(ostr(5132.5_Js) == "5132.5 J.s");
    }

    SECTION("exponent unit output")
    {
        REQUIRE(ostr(185_m2) == u8"185 m\u00B2");
        REQUIRE(ostr(10.5_m3) == u8"10.5 m\u00B3");
    }

    SECTION("complex unit output")
    {
        REQUIRE(ostr(5_J_p_kgK) == u8"5 J.kg\u207B\u00B9.K\u207B\u00B9");
        REQUIRE(ostr(5.2_J_p_kgK) == u8"5.2 J.kg\u207B\u00B9.K\u207B\u00B9");
    }

    SECTION("custome unit output")
    {
        REQUIRE(ostr(40.5_L_p_min) == u8"40.5 L.min\u207B\u00B9");
        REQUIRE(ostr(3600_L_p_h) == u8"3600 L.h\u207B\u00B9");
        REQUIRE(ostr(30_ccm) == "30 ccm");
    }
}
