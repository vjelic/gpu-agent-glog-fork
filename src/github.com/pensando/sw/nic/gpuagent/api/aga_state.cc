
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
/// This file contains implementation of agent state class
///
//----------------------------------------------------------------------------

#include <sys/time.h>
#include <sys/resource.h>
#include "nic/gpuagent/core/trace.hpp"
#include "nic/gpuagent/api/mem.hpp"
#include "nic/gpuagent/api/aga_state.hpp"

namespace aga {

/// singleto instance of all agent state
aga_state g_aga_state;

aga_state::aga_state() {
    memset(state_, 0, sizeof(state_));
}

aga_state::~aga_state() {
}

void
aga_state::store_init_(void) {
    state_[AGA_STATE_GPU] = new gpu_state();
    state_[AGA_STATE_GPU_WATCH] = new gpu_watch_state();
}

sdk_ret_t
aga_state::init(void) {
    // initialize all the internal databases
    store_init_();
    return SDK_RET_OK;
}

void
aga_state::destroy(aga_state *ps) {
    for (uint32_t i = AGA_STATE_MIN + 1; i < AGA_STATE_MAX; i++) {
        if (ps->state_[i]) {
            delete ps->state_[i];
        }
    }
}

sdk_ret_t
aga_state::walk(state_walk_cb_t walk_cb, void *ctxt) {
    state_walk_ctxt_t walk_ctxt;

    for (uint32_t i = AGA_STATE_MIN + 1; i < AGA_STATE_MAX; i ++) {
        if (state_[i]) {
            walk_ctxt.name.assign(AGA_STATE_str(aga_state_t(i)));
            walk_ctxt.state = state_[i];
            walk_cb(&walk_ctxt, ctxt);
        }
    }
    return SDK_RET_OK;
}

}    // namespace aga
