/*
    Copyright (C) 2013-2014 Remi Thebault
    All rights reserved.

    This program and its source code are distributed under the
    terms of the BSD-style license, that can be found in the
    License.txt file at project root.
*/

#ifndef QPHYSICS_API_HPP
#define QPHYSICS_API_HPP

#include "QtCore/qglobal.h"

#ifndef QPHYSICS_NODLL

#if defined(QPHYSICSUI_LIBRARY)
#   define QPHYSICSUI_API Q_DECL_EXPORT
#else
#   define QPHYSICSUI_API Q_DECL_IMPORT
#endif

#else
#define QPHYSICSUI_API
#endif

#endif // QPHYSICS_API_HPP
