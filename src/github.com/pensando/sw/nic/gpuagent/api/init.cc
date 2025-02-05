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
/// API layer init/cleanup routines
///
//----------------------------------------------------------------------------

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/sdk/include/sdk/assert.hpp"
#include "nic/gpuagent/core/trace.hpp"
#include "nic/gpuagent/core/api_thread.hpp"
#include "nic/gpuagent/api/include/aga_init.hpp"
#include "nic/gpuagent/api/aga_state.hpp"
#include "nic/gpuagent/api/smi/smi_api.hpp"

sdk_ret_t
aga_api_init (aga_api_init_params_t *init_params)
{
    sdk_ret_t ret;

    // initialize the internal state
    ret = aga::g_aga_state.init();
    SDK_ASSERT(ret() == SDK_RET_OK);
    // spawn the API thread
    aga::spawn_api_thread(&aga::g_aga_state);
    // wait for the API thread to be ready
    while (!aga::is_api_thread_ready()) {
        sched_yield();
    }
    // initialize rocm-smi library
    ret = aga::smi_init(init_params);
    if (unlikely(ret != SDK_RET_OK)) {
        AGA_TRACE_ERR("Failed to initialize smi library, err {}", ret());
        return SDK_RET_ERR;
    }
    return SDK_RET_OK;
}

sdk_ret_t
aga_api_teardown (void)
{
    return SDK_RET_OK;
}
