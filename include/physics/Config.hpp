/*
	Copyright (C) 2013-2014 Remi Thebault
	All rights reserved.

	This program and its source code are distributed under the
	terms of the BSD-style license, that can be found in the
	License.txt file at project root.
*/

#ifndef PHYSICS_CONFIG_HPP
#define PHYSICS_CONFIG_HPP


// uncomment the following line if your compiler do not support constexpr
// #define PHYSICS_NO_CONSTEXPR

// uncomment the following line if your compiler do not support user defined literals
// #define PHYSICS_NO_LITERALS


#if __cplusplus < 201103L

# ifndef PHYSICS_NO_CONSTEXPR
#  define PHYSICS_NO_CONSTEXPR
# endif

# ifndef PHYSICS_NO_LITERALS
#  define PHYSICS_NO_LITERALS
# endif

#endif


#ifndef PHYSICS_NO_CONSTEXPR

#define PHYSICS_CONSTEXPR constexpr
#define PHYSICS_INCLASS_CONSTEXPR constexpr

#else

#define PHYSICS_CONSTEXPR inline
#define PHYSICS_INCLASS_CONSTEXPR

#endif



#endif // PHYSX_CONFIG_HPP
