/*
        Copyright (c) 2013 2014, Plastic Omnium Auto INERGY
        All rights reserved.

        Copy and redistribution of this program in source or binary forms,
        with or without modification, are strictly forbidden.
*/

#include "ph/Physics.hpp"

#include "catch.hpp"



TEST_CASE("Zero", "[zero]")
{

    SECTION("comparison") {

        REQUIRE(ph::Volume{} == ph::zero);
        REQUIRE(ph::Volume::fromM3(1.0) > ph::zero);
        REQUIRE(ph::Volume::fromM3(-1.0) < ph::zero);

    }


}

