/*
	Copyright (C) 2013-2014 Remi Thebault
	All rights reserved.

	This program and its source code are distributed under the
	terms of the BSD-style license, that can be found in the
	License.txt file at project root.
*/

#ifndef PHYSX_PHYSX_HPP
#define PHYSX_PHYSX_HPP

#include "Config.hpp"

#include "_IncludeAll.hpp"

#include "Operators.hpp"
#include "Constants.hpp"

#ifndef PHYSICS_NO_LITERALS
#include "Literals.hpp"
#endif

namespace Physics {

	// a few goodies

	PHYSICS_CONSTEXPR Length circle (const Length& radius)
	{
		return 2 * pi() * radius;
	}

	PHYSICS_CONSTEXPR Area disk (const Length& radius)
	{
		return pi() * radius * radius;
	}

	PHYSICS_CONSTEXPR Volume sphere (const Length& radius)
	{
		return radius * radius * radius * 4.0 / 3.0;
	}




	PHYSICS_CONSTEXPR double density(const VolumicMass& vm) {
		return vm.kgpl();
	}




	PHYSICS_CONSTEXPR Energy cineticEnergy(const Mass& m, const Velocity& v)
	{
		return Energy::fromJ(0.5 * m.kg() * v.mps() * v.mps());
	}

}

#endif // PHYSX_PHYSX_HPP
