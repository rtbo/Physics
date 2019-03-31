/*
    Copyright (C) 2013-2019 Remi Thebault
    All rights reserved.

    This program and its source code are distributed under the
    terms of the BSD-style license, that can be found in the
    License.txt file at project root.
*/

#include <si/Temperature.hpp>

#include "catch.hpp"

using namespace si::literals;

TEST_CASE("Temperature", "[temperature]") {

    SECTION("default construct") {
        REQUIRE(si::Temperature{} == 0_K);
        REQUIRE(si::Temperature{} == si::kelvin_t{ 0 });
    }

    SECTION("conversion") {
        REQUIRE(0_K == -273.15_degC);
        REQUIRE(20_degC == 293.15_K);
    }

    SECTION("farenheit") {
        REQUIRE(0_degF > -18_degC);
        REQUIRE(0_degF < -17.5_degC);

        REQUIRE(100_degF > 37.5_degC);
        REQUIRE(100_degF < 38_degC);
    }
}
