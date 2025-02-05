
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
/// generic API operation definitions
//----------------------------------------------------------------------------

#ifndef __AGA_CORE_API_H__
#define __AGA_CORE_API_H__

#include "nic/sdk/include/sdk/base.hpp"

// TODO:
// explore adding namespace here and in obj.h and get rid of aga_ prefix for
// enums

#ifdef __cplusplus
extern "C" {
#endif

/// \brief    max. size of API object name
#define AGA_OBJ_NAME_SIZE        32

/// \brief    API operations
typedef enum api_op_e {
    API_OP_NONE,       ///< none
    API_OP_CREATE,     ///< create
    API_OP_DELETE,     ///< delete
    API_OP_UPDATE,     ///< update
    API_OP_INVALID,    ///< invalid
} api_op_t;

/// \brief    helper API to validate the API call
/// \param[in] op      API operation
/// \param[in] key     key of the object
/// \param[in] spec    config specification of the object
/// \return    SDK_RET_OK or error code in case of failure
static inline sdk_ret_t
obj_api_validate (api_op_t op, void *key, void *spec)
{
    if ((op == API_OP_DELETE) && key) {
        return SDK_RET_OK;
    }

    if (((op == API_OP_CREATE) || (op == API_OP_UPDATE)) && spec) {
        return SDK_RET_OK;
    }
    return SDK_RET_INVALID_ARG;
}

#ifdef __cplusplus
}
#endif

#endif    // __AGA_CORE_API_H__
