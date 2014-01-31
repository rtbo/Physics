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

#if defined(QPHYSICS_LIBRARY)
#   define QPHYSICS_API Q_DECL_EXPORT
#else
#   define QPHYSICS_API Q_DECL_IMPORT
#endif

#else
#define QPHYSICS_API
#endif

#endif // QPHYSICS_API_HPP
