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

TEST_CASE("Molecular Mass", "[molecularMass][quantity][mass]")
{

	SECTION("conversion") {

		// molecular mass of carbon
		REQUIRE(MolecularMass::fromKgpmol(0.012) == MolecularMass::fromGpmol(12.0));

	}

}
