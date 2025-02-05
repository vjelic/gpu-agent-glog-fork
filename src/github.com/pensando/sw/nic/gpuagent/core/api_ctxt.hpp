
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
/// this file deals with internal API context information
///
//----------------------------------------------------------------------------

#ifndef __AGA_CORE_API_CTXT_HPP__
#define __AGA_CORE_API_CTXT_HPP__

#include "nic/gpuagent/core/api_params.hpp"
#include "nic/gpuagent/core/trace.hpp"

namespace aga {

/// async response callback type
typedef void (*aga_async_rsp_cb_t)(sdk_ret_t status, const void *cookie);

/// \brief API specific parameters
/// \brief Per API context maintained by core framework while processing an API
typedef struct api_ctxt_s {
    /// API operation
    api_op_t api_op;
    /// object identifier
    obj_id_t obj_id;
    /// API specific params
    api_params_base *api_params;
    /// synchronous/asynchronous API processing
    bool async;
    //// response callback in case this is asynchronous request
    aga_async_rsp_cb_t response_cb;
    /// opaque cookie used to correlate requests and responses
    void *cookie;
} api_ctxt_t;

static inline api_ctxt_t *
api_ctxt_alloc (obj_id_t obj_id, api_op_t api_op)
{
    api_ctxt_t *api_ctxt;

    api_ctxt = (api_ctxt_t *)calloc(1, sizeof(api_ctxt_t));
    if (api_ctxt) {
        api_ctxt->obj_id = obj_id;
        api_ctxt->api_op = api_op;
        api_ctxt->api_params = api_params_base::factory();
        if (unlikely(api_ctxt->api_params == NULL)) {
            free(api_ctxt);
            return NULL;
        }
    }
    return api_ctxt;
}

static inline void
api_ctxt_free (api_ctxt_t *api_ctxt)
{
    if (api_ctxt->api_params) {
        api_params_base::destroy(api_ctxt->obj_id, api_ctxt->api_op,
                                 api_ctxt->api_params);
    }
    free(api_ctxt);
}

}    // namespace aga

using aga::api_ctxt_t;

#endif    // __AGA_CORE_API_CTXT_HPP__
