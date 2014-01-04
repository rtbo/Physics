/*
	Copyright (C) 2013-2014 Remi Thebault
	All rights reserved.

	This program and its source code are distributed under the
	terms of the BSD-style license, that can be found in the
	License.txt file at project root.
*/

#ifndef PHYSICS_OPERATORS_HPP
#define PHYSICS_OPERATORS_HPP

#include "Config.hpp"


#include "_IncludeAll.hpp"


namespace Physics {


	// deducing common operators from == and <

	template <class T>
	constexpr bool operator!=(const T& lhs, const T& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T>
	constexpr bool operator>(const T& lhs, const T& rhs)
	{
		return rhs < lhs;
	}

	template <class T>
	constexpr bool operator<=(const T& lhs, const T& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T>
	constexpr bool operator>=(const T& lhs, const T& rhs)
	{
		return !(lhs < rhs);
	}



	constexpr Area operator*(Length lhs, Length rhs)
	{
		return Area::fromM2(lhs.m() * rhs.m());
	}

	constexpr Volume operator*(Length lhs, Area rhs)
	{
		return Volume::fromM3(lhs.m() * rhs.m2());
	}

	constexpr Volume operator*(Area lhs, Length rhs)
	{
		return rhs * lhs;
	}



	constexpr Velocity operator/(Length lhs, Time rhs)
	{
		return Velocity::fromMps(lhs.m() / rhs.s());
	}

	constexpr Acceleration operator/(Velocity lhs, Time rhs)
	{
		return Acceleration::fromMps2(lhs.mps() / rhs.s());
	}



	constexpr Flow operator/(Volume lhs, Time rhs)
	{
		return Flow::fromM3ps(lhs.m3() / rhs.s());
	}

	constexpr Volume operator*(Flow lhs, Time rhs)
	{
		return Volume::fromM3(lhs.m3ps() * rhs.s());
	}


	constexpr Pressure operator/(Force lhs, Area rhs)
	{
		return Pressure::fromPa(lhs.N() / rhs.m2());
	}

	constexpr Force operator*(Pressure lhs, Area rhs)
	{
		return Force::fromN(lhs.Pa() * rhs.m2());
	}

	constexpr Force operator*(Area lhs, Pressure rhs)
	{
		return rhs * lhs;
	}


	constexpr Force operator*(Mass lhs, Acceleration rhs)
	{
		return Force::fromN(lhs.kg() * rhs.mps2());
	}

	constexpr Force operator*(Acceleration lhs, Mass rhs)
	{
		return rhs * lhs;
	}



	constexpr VolumicMass operator/(Mass lhs, Volume rhs)
	{
		return VolumicMass::fromKgpm3(lhs.kg() / rhs.m3());
	}

	constexpr Volume operator/(Mass lhs, VolumicMass rhs)
	{
		return Volume::fromM3(lhs.kg() / rhs.kgpm3());
	}

	constexpr Mass operator*(Volume lhs, VolumicMass rhs)
	{
		return Mass::fromKg(lhs.m3() * rhs.kgpm3());
	}

	constexpr Mass operator*(VolumicMass lhs, Volume rhs)
	{
		return rhs * lhs;
	}

}

#endif // PHYSX_OPERATORS_HPP
