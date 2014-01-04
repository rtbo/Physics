/*
	Copyright (C) 2013-2014 Remi Thebault
	All rights reserved.

	This program and its source code are distributed under the
	terms of the BSD-style license, that can be found in the
	License.txt file at project root.
*/

#include "physics/Temperature.hpp"

#include "catch.hpp"

using namespace Physics;

TEST_CASE("Temperature", "[temperature]")
{

	SECTION("default construct") {

		REQUIRE(Temperature{} == Temperature::fromK(0.0));

	}

	SECTION("conversion") {

		REQUIRE(Temperature{} == Temperature::fromDegC(-273.15));

	}


}
