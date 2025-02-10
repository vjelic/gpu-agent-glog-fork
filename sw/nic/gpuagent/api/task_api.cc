
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
/// this file implements task CRUD APIs
///
//----------------------------------------------------------------------------

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/core/trace.hpp"
#include "nic/gpuagent/core/api.h"
#include "nic/gpuagent/core/api_ctxt.hpp"
#include "nic/gpuagent/core/api_msg.hpp"
#include "nic/gpuagent/api/include/base.hpp"
#include "nic/gpuagent/api/internal/aga_api_params.hpp"
#include "nic/gpuagent/api/include/aga_task.hpp"

static sdk_ret_t
aga_task_api_handle (api_op_t op, aga_obj_key_t *key, aga_task_spec_t *spec)
{
    sdk_ret_t ret;
    api_ctxt_t *api_ctxt;

    if ((ret = obj_api_validate(op, key, spec)) != SDK_RET_OK) {
        // basic API validation failure
        return ret;
    }
    // allocate API context
    api_ctxt = aga::api_ctxt_alloc(AGA_OBJ_ID_TASK, op);
    if (likely(api_ctxt != NULL)) {
        if (op == API_OP_DELETE) {
            AGA_API_PARAMS_FROM_API_CTXT(api_ctxt)->key = *key;
        } else {
            AGA_API_PARAMS_FROM_API_CTXT(api_ctxt)->task_spec = *spec;
        }
        return process_api(api_ctxt);
    }
    return SDK_RET_OOM;
}

sdk_ret_t
aga_task_create (_In_ aga_task_spec_t *spec)
{
    return aga_task_api_handle(API_OP_CREATE, NULL, spec);
}
