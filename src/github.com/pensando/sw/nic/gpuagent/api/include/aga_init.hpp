
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
/// initialization APIs
///
//----------------------------------------------------------------------------

#ifndef __API_INCLUDE_AGA_INIT_HPP__
#define __API_INCLUDE_AGA_INIT_HPP__

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/api/include/aga_event.hpp"

/// \brief    initialization parameters
typedef struct aga_api_init_params_s {
} aga_api_init_params_t;

/// \brief    initialization routine for API layer
/// \param[in] init_params    init time parameters
/// \return #SDK_RET_OK on success, failure status code on error
sdk_ret_t aga_api_init(aga_api_init_params_t *init_params);

/// \brief    cleanup routine for API layer
/// \return #SDK_RET_OK on success, failure status code on error
sdk_ret_t aga_api_teardown(void);

#endif    /// __API_INCLUDE_AGA_INIT_HPP__
