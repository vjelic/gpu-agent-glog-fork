//
// Copyright(C) Advanced Micro Devices, Inc. All rights reserved.
//
// You may not use this software and documentation (if any) (collectively,
// the "Materials") except in compliance with the terms and conditions of
// the Software License Agreement included with the Materials or otherwise as
// set forth in writing and signed by you and an authorized signatory of AMD.
// If you do not have a copy of the Software License Agreement, contact your
// AMD representative for a copy.
//
// You agree that you will not reverse engineer or decompile the Materials,
// in whole or in part, except as allowed by applicable law.
//
// THE MATERIALS ARE DISTRIBUTED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
// REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
//


//----------------------------------------------------------------------------
///
/// \file
/// assert definitions
///
//----------------------------------------------------------------------------

#ifndef __SDK_ASSERT_HPP__
#define __SDK_ASSERT_HPP__

#include <assert.h>
#include "lib/logger/logger.h"

#ifdef __cplusplus
namespace sdk {
#endif

#define __ASSERT__(x)       assert(x)

#define SDK_ASSERT_RETURN(cond, rv)                        \
do {                                                       \
    if (unlikely(!(cond))) {                               \
        SDK_TRACE_ERR("ASSERT FAILURE(" #cond ")");        \
        __ASSERT__(FALSE);                                 \
        return rv;                                         \
    }                                                      \
} while (FALSE)

#define SDK_ASSERT_TRACE_RETURN(cond, rv, args...)         \
do {                                                       \
    if (unlikely(!(cond))) {                               \
        SDK_TRACE_ERR("ASSERT FAILURE(" #cond ")");        \
        SDK_TRACE_ERR(args);                               \
        __ASSERT__(FALSE);                                 \
        return rv;                                         \
    }                                                      \
} while (FALSE)


#define SDK_ASSERT_RETURN_VOID(cond)                       \
do {                                                       \
    if (unlikely(!(cond))) {                               \
        SDK_TRACE_ERR("ASSERT FAILURE(" #cond ")");        \
        __ASSERT__(FALSE);                                 \
        return;                                            \
    }                                                      \
} while (FALSE)

#define SDK_ASSERT_GOTO(cond, label)                       \
do {                                                       \
    if (unlikely(!(cond))) {                               \
        SDK_TRACE_ERR("ASSERT FAILURE(" #cond ")");        \
        goto label;                                        \
    }                                                      \
} while (FALSE)

#define SDK_ASSERT_TRACE_GOTO(cond, label, args...)        \
do {                                                       \
    if (unlikely(!(cond))) {                               \
        SDK_TRACE_ERR("ASSERT FAILURE(" #cond ")");        \
        SDK_TRACE_ERR(args);                               \
        __ASSERT__(FALSE);                                 \
        goto label;                                         \
    }                                                      \
} while (FALSE)

#define SDK_ASSERT(cond)        __ASSERT__(cond)

#define SDK_ABORT(cond)                                    \
do {                                                       \
    if (unlikely(!(cond))) {                               \
        abort();                                           \
    }                                                      \
} while (FALSE)

#define SDK_ABORT_TRACE(cond, args...)                     \
do {                                                       \
    if (unlikely(!(cond))) {                               \
        SDK_TRACE_ERR(args);                               \
        abort();                                           \
    }                                                      \
} while (FALSE)

#ifdef __cplusplus
}    // namespace sdk
#endif   // __cplusplus

#endif    // __SDK_ASSERT_HPP__

