/*
	Copyright (C) 2013-2014 Remi Thebault
	All rights reserved.

	This program and its source code are distributed under the
	terms of the BSD-style license, that can be found in the
	License.txt file at project root.
*/

#include "physics/Physics.hpp"

#include "catch.hpp"

using namespace Physics;

TEST_CASE("Volumic Mass", "[volumicMass][volume][mass][density]")
{

	SECTION("conversion") {

		// volumic mass of gasoline
		REQUIRE(VolumicMass::fromKgpm3(750.0) == VolumicMass::fromKgpl(0.75));

	}

	SECTION("density") {

		// density of gasoline
		REQUIRE(density(VolumicMass::fromKgpm3(750.0)) == 0.75);

	}


}
