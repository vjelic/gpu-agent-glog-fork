
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
/// API params specific APIs
///
//----------------------------------------------------------------------------

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/core/trace.hpp"
#include "nic/gpuagent/core/api.h"
#include "nic/gpuagent/core/api_params.hpp"
#include "nic/gpuagent/api/mem.hpp"
#include "nic/gpuagent/api/aga_state.hpp"
#include "nic/gpuagent/api/internal/aga_api_params.hpp"

namespace aga {

api_params_base *
api_params_base::factory(void) {
    void *mem;

    mem = g_aga_state.aga_api_params_alloc();
    new (mem) aga_api_params();
    return (api_params_base *)mem;
}

void
api_params_base::destroy(obj_id_t obj_id, api_op_t api_op,
                         api_params_base *api_params) {
    //aga_api_params *params;

    //params = (aga_api_params *)api_params;
    switch (obj_id) {
        default:
            break;
    }
    g_aga_state.aga_api_params_free(api_params);
}

const aga_obj_key_t&
aga_api_params::obj_key(obj_id_t obj_id, api_op_t api_op) {
    // for delete operations, key is stored in one for all objects
    if (api_op == API_OP_DELETE) {
        return key;
    }
    // for create & update, look into the object
    switch (obj_id) {
    case AGA_OBJ_ID_GPU:
        return gpu_spec.key;
    case AGA_OBJ_ID_TASK:
        return task_spec.key;
    case AGA_OBJ_ID_GPU_WATCH:
        return gpu_watch_spec.key;
    default:
        AGA_TRACE_ERR("Unknown object id {}", obj_id);
        break;
    }
    SDK_ASSERT(FALSE);
    return k_aga_obj_key_invalid;
}

}    // namespace aga
