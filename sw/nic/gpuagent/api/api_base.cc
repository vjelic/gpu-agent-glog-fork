
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
/// this file deals with base object definition for all API objects
///
//----------------------------------------------------------------------------

#include "nic/gpuagent/core/trace.hpp"
//#include "nic/gpuagent/core/core/msg.h"
#include "nic/gpuagent/api/aga_state.hpp"
#include "nic/gpuagent/core/api_base.hpp"
#include "nic/gpuagent/core/api_params.hpp"
#include "nic/gpuagent/core/api_ctxt.hpp"
#include "nic/gpuagent/api/internal/aga_api_params.hpp"

namespace aga {

api_base *
api_base::factory(api_ctxt_t *api_ctxt) {
    aga_api_params *api_params;

    api_params = AGA_API_PARAMS_FROM_API_CTXT(api_ctxt);
    switch (api_ctxt->obj_id) {
    case AGA_OBJ_ID_GPU:
        return gpu_entry::factory(&api_params->gpu_spec);

    case AGA_OBJ_ID_GPU_WATCH:
        return gpu_watch_entry::factory(&api_params->gpu_watch_spec);

    case AGA_OBJ_ID_TASK:
        return task::factory(&api_params->task_spec);

    default:
        AGA_TRACE_ERR("factory method not implemented for obj {}",
                      api_ctxt->obj_id);
        break;
    }
    return NULL;
}


sdk_ret_t
api_base::free(obj_id_t obj_id, api_base *api_obj) {
    switch (obj_id) {
    case AGA_OBJ_ID_GPU:
        return gpu_entry::free((gpu_entry *)api_obj);

    case AGA_OBJ_ID_GPU_WATCH:
        return gpu_watch_entry::free((gpu_watch_entry *)api_obj);

    case AGA_OBJ_ID_TASK:
        return task::free((task *)api_obj);

    default:
        AGA_TRACE_ERR("free not implemented for obj {}", obj_id);
        break;
    }
    return SDK_RET_ERR;
}

api_base *
api_base::find_obj(api_ctxt_t *api_ctxt) {
    aga_api_params *api_params;

    api_params = AGA_API_PARAMS_FROM_API_CTXT(api_ctxt);
    switch (api_ctxt->obj_id) {
    case AGA_OBJ_ID_GPU:
        if (api_ctxt->api_op == API_OP_DELETE) {
            return gpu_db()->find(&api_params->key);
        }
        return gpu_db()->find(&api_params->gpu_spec.key);

    case AGA_OBJ_ID_GPU_WATCH:
        if (api_ctxt->api_op == API_OP_DELETE) {
            return gpu_watch_db()->find(&api_params->key);
        }
        return gpu_watch_db()->find(&api_params->gpu_watch_spec.key);

    case AGA_OBJ_ID_TASK:
        return task_db()->find(&api_params->task_spec.key);

    default:
        AGA_TRACE_ERR("find not implemented for obj id {}",
                      api_ctxt->obj_id);
        break;
    }
    return NULL;
}

bool
api_base::stateless(obj_id_t obj_id) {
    switch (obj_id) {
    case AGA_OBJ_ID_TASK:
        return true;
    default:
        break;
    }
    return false;
}

}    // namespace aga
