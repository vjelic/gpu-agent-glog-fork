
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
/// API handlers definitions that all objects are expected to implement
//----------------------------------------------------------------------------

#ifndef __AGA_API_HANDLERS_HPP__
#define __AGA_API_HANDLERS_HPP__

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/core/api.h"
#include "nic/gpuagent/core/obj.h"
#include "nic/gpuagent/core/trace.hpp"
#include "nic/gpuagent/core/api_base.hpp"
#include "nic/gpuagent/core/api_ctxt.hpp"
#include "nic/gpuagent/core/api_params.hpp"

namespace aga {

/// \brief    create callback on an object
/// \param[in] api_obj    new object instantiated to handle create operation
/// \param[in] api_params API params containing the context of the API call
/// \return    SDK_RET_OK or error code in case of failure
typedef sdk_ret_t (*aga_obj_create_cb_t)(api_base *api_obj,
                                         api_params_base *api_params);
/// \brief    delete callback on an object
/// \param[in] api_obj    object being deleted
/// \param[in] api_params API params containing the context of the API call
/// \return    SDK_RET_OK or error code in case of failure
typedef sdk_ret_t (*aga_obj_delete_cb_t)(api_base *api_obj,
                                         api_params_base *api_params);
/// \brief    update callback on an object
/// \param[in] api_obj    object being updated
/// \param[in] api_params API params containing the context of the API call
/// \return    SDK_RET_OK or error code in case of failure
typedef sdk_ret_t (*aga_obj_update_cb_t)(api_base *api_obj,
                                         api_params_base *api_params);

/// \brief    per object callbacks in one place
typedef struct aga_obj_api_cb_s {
    /// API handler to handle create operation
    aga_obj_create_cb_t create_cb;
    /// API handler to handle delete operation
    aga_obj_delete_cb_t delete_cb;
    /// API handler to handle update operation
    aga_obj_update_cb_t update_cb;
} aga_obj_api_cb_t;

// g_api_obj_cb needs to be implemented by the agent
extern aga_obj_api_cb_t g_api_obj_cb[AGA_OBJ_ID_MAX];

}    // namespace aga

#endif    // __AGA_API_HANDLERS_HPP__
