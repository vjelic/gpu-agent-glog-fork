
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
/// object identifier definitions
//----------------------------------------------------------------------------

#ifndef __AGA_CORE_OBJ_H__
#define __AGA_CORE_OBJ_H__

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/// \brief    object identifiers
typedef enum obj_id_e {
    AGA_OBJ_ID_NONE      = 0,
    /// GPU object
    AGA_OBJ_ID_GPU       = 1,
    /// generic task object
    AGA_OBJ_ID_TASK      = 2,
    /// GPU watch object
    AGA_OBJ_ID_GPU_WATCH = 3,
    AGA_OBJ_ID_MAX
} obj_id_t;

/// \brief    max. size of API object name
#define AGA_OBJ_NAME_SIZE        32


#ifdef __cplusplus
}
#endif

#endif    // __AGA_CORE_OBJ_H__
