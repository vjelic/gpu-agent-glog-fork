
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
/// gpu object CRUD API handlers
///
//----------------------------------------------------------------------------

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/core/api_base.hpp"
#include "nic/gpuagent/core/api_params.hpp"
#include "nic/gpuagent/api/internal/aga_api_params.hpp"

namespace aga {

sdk_ret_t
aga_gpu_create_cb (api_base *api_obj, api_params_base *api_params)
{
    return api_obj->create_handler(api_params);
}

sdk_ret_t
aga_gpu_delete_cb (api_base *api_obj, api_params_base *api_params)
{
    return api_obj->delete_handler(api_params);
}

sdk_ret_t
aga_gpu_update_cb (api_base *api_obj, api_params_base *api_params)
{
    return api_obj->update_handler(api_params);
}

}    // namespace aga
