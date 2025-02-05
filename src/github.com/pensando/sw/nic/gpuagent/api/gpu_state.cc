
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
/// gpu state handling
///
//----------------------------------------------------------------------------

#include "nic/sdk/include/sdk/mem.hpp"
#include "nic/gpuagent/core/trace.hpp"
#include "nic/gpuagent/api/mem.hpp"
#include "nic/gpuagent/api/aga_state.hpp"
#include "nic/gpuagent/api/gpu_state.hpp"

namespace aga {

/// \defgroup AGA_GPU_STATE - gpu database functionality
/// \ingroup AGA_GPU
/// \@{

gpu_entry *
gpu_state::alloc(void) {
    return (gpu_entry *)calloc(1, sizeof(gpu_entry));
}

sdk_ret_t
gpu_state::insert(gpu_entry *gpu) {
    sdk_ret_t ret;

    AGA_TRACE_DEBUG("Inserting GPU {} in db", gpu->key_.str());
    auto it = gpu_key_db_.find(gpu->key_);
    if (it != gpu_key_db_.end()) {
        AGA_STATE_CNTR_INSERT_ERR_INC();
        ret = SDK_RET_ENTRY_EXISTS;
    } else {
        gpu_key_db_[gpu->key_] = gpu;
        AGA_STATE_CNTR_INSERT_OK_INC();
        AGA_STATE_CNTR_NUM_ELEMS_INC();
        ret = SDK_RET_OK;
    }
    return ret;
}

sdk_ret_t
gpu_state::insert_in_handle_db(gpu_entry *gpu) {
    sdk_ret_t ret;

    AGA_TRACE_DEBUG("Inserting GPU {} with handle {} in db", gpu->key_.str(),
                    gpu->handle_);
    gpu_db_[gpu->handle_] = gpu;
    return ret;
}

gpu_entry *
gpu_state::remove(gpu_entry *gpu) {
    void *rv;

    auto it = gpu_key_db_.find(gpu->key_);
    if (it == gpu_key_db_.end()) {
        AGA_STATE_CNTR_REMOVE_ERR_INC();
        rv = NULL;
    } else {
        rv = it->second;
        gpu_key_db_.erase(gpu->key_);
        // remove from handles db
        gpu_db_.erase(gpu->handle_);
        AGA_STATE_CNTR_REMOVE_OK_INC();
        AGA_STATE_CNTR_NUM_ELEMS_DEC();
    }
    return (gpu_entry *)rv;
}

void
gpu_state::free(gpu_entry *gpu) {
    free(gpu);
}

gpu_entry *
gpu_state::find(aga_obj_key_t *key) const {
    auto it = gpu_key_db_.find(*key);
    if (it != gpu_key_db_.end()) {
        return it->second;
    }
    return NULL;
}

gpu_entry *
gpu_state::find(aga_gpu_handle_t handle) const {
    auto it = gpu_db_.find(handle);
    if (it != gpu_db_.end()) {
        return it->second;
    }
    return NULL;
}

sdk_ret_t
gpu_state::walk(state_walk_cb_t walk_cb, void *ctxt) {
    bool stop;

    for (auto iter = gpu_key_db_.begin(); iter != gpu_key_db_.end(); ++iter) {
        stop = walk_cb(iter->second, ctxt);
        if (stop) {
            break;
        }
    }
    return SDK_RET_OK;
}

sdk_ret_t
gpu_state::walk_handle_db(state_walk_cb_t walk_cb, void *ctxt) {
    bool stop;

    for (auto iter = gpu_db_.begin(); iter != gpu_db_.end(); ++iter) {
        stop = walk_cb(iter->second, ctxt);
        if (stop) {
            break;
        }
    }
    return SDK_RET_OK;
}

/// \@}    // end of AGA_GPU_STATE

}    // namespace aga
