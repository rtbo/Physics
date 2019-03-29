/*
    Copyright (C) 2013-2014 Remi Thebault
    All rights reserved.

    This program and its source code are distributed under the
    terms of the BSD-style license, that can be found in the
    License.txt file at project root.
*/


#include <si/Operations.hpp>
#include <si/MolarMass.hpp>

#include "catch.hpp"

using namespace si::literals;

TEST_CASE("Molar Mass", "[molarMass][quantity][mass]")
{

    SECTION("conversion") {

        // molar mass of carbon
        REQUIRE(0.012_kg_p_mol == 12_g_p_mol);

    }

}
