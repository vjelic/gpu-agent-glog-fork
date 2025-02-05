
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
/// APIs for memory mgmt.
///
//----------------------------------------------------------------------------

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/core/trace.hpp"
#include "nic/gpuagent/api/mem.hpp"
#include "nic/gpuagent/api/gpu.hpp"
#include "nic/gpuagent/api/gpu_watch.hpp"

namespace aga {

/// \brief callback invoked by the delay delete function to release an object
/// \param[in]    obj_id     object identifier
/// \param[in]    elem       element to free
static inline void
delay_delete_cb (uint32_t obj_id, void *elem)
{
    AGA_TRACE_VERBOSE("obj {}, elem {}", obj_id, elem);
    switch (obj_id) {
    case AGA_OBJ_ID_GPU:
        gpu_entry::destroy((gpu_entry *)elem);
        break;
    case AGA_OBJ_ID_GPU_WATCH:
        gpu_watch_entry::destroy((gpu_watch_entry *)elem);
        break;
    default:
        AGA_TRACE_ERR("Unknown object {}", obj_id);
        SDK_ASSERT(FALSE);
    }
    return;
}

/// \brief entry function for delay delete thread
/// \param[in] obj_id           object identifier
/// \param[in] elem             element to free
/// \param[in] timeout_secs     delay in secs
static void
delay_delete_thread_entry (uint32_t obj_id, void *elem, uint64_t timeout_secs)
{
    // sleep for specific delay secs
    sleep(timeout_secs);
    AGA_TRACE_VERBOSE("Deleting object {} type {}", elem, obj_id);
    // delete the object
    delay_delete_cb(obj_id, elem);
}

/// \brief function to delete element after delay
/// \param[in] obj_id           object identifier
/// \param[in] elem             element to free
/// \param[in] timeout_secs     delay in secs
/// \return SDK_RET_OK on success, failure status code on error
sdk_ret_t
delay_delete (uint32_t obj_id, void *elem, uint64_t timeout_secs)
{
    if (obj_id >= AGA_OBJ_ID_MAX) {
        AGA_TRACE_ERR("Unexpected object {}", obj_id);
        return SDK_RET_INVALID_ARG;
    }
    AGA_TRACE_VERBOSE("Scheduling object {} type {} for delay delete, "
                      "after {} seconds", elem, obj_id, timeout_secs);
    // start a thread to handle delay delete
    std::thread(delay_delete_thread_entry, obj_id, elem, timeout_secs).detach();
    return SDK_RET_OK;
}

}    // namespace aga
