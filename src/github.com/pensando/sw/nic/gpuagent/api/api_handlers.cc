
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
/// API handlers for all supported objects
//----------------------------------------------------------------------------

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/core/api.h"
#include "nic/gpuagent/core/trace.hpp"
#include "nic/gpuagent/core/api_base.hpp"
#include "nic/gpuagent/core/api_ctxt.hpp"
#include "nic/gpuagent/core/api_cb.hpp"
#include "nic/gpuagent/api/gpu.hpp"
#include "nic/gpuagent/api/gpu_watch.hpp"
#include "nic/gpuagent/api/task.hpp"

namespace aga {

static inline sdk_ret_t
aga_invalid_op_cb (api_base *api_obj, api_params_base *api_params)
{
    return SDK_RET_INVALID_OP;
}

aga_obj_api_cb_t g_api_obj_cb[] = {
    // AGA_OBJ_ID_NONE
    {
        NULL,
        NULL,
        NULL,
    },
    // AGA_OBJ_ID_GPU
    {
        aga_gpu_create_cb,
        aga_gpu_delete_cb,
        aga_gpu_update_cb,
    },
    // AGA_OBJ_ID_TASK
    {
        aga_task_create_cb,
        aga_invalid_op_cb,
        aga_invalid_op_cb,
    },
    // AGA_OBJ_ID_GPU_WATCH
    {
        aga_gpu_watch_create_cb,
        aga_gpu_watch_delete_cb,
        aga_gpu_watch_update_cb,
    }
};

}    // namespace aga
