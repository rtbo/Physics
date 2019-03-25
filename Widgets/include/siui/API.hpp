/*
    Copyright (C) 2013-2019 Remi Thebault
    All rights reserved.

    This program and its source code are distributed under the
    terms of the BSD-style license, that can be found in the
    License.txt file at project root.
*/

#ifndef SIUI_API_HPP
#define SIUI_API_HPP

#include "QtCore/qglobal.h"

#ifndef SIUI_NODLL

#if defined(SIUI_LIBRARY)
#   define SIUI_API Q_DECL_EXPORT
#else
#   define SIUI_API Q_DECL_IMPORT
#endif

#else
#define SIUI_API
#endif

#endif // SIUI_API_HPP
