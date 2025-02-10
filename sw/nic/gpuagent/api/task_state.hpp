
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
/// task state handling
///
//----------------------------------------------------------------------------

#ifndef __AGA_TASK_STATE_HPP__
#define __AGA_TASK_STATE_HPP__

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/sdk/include/sdk/mem.hpp"
#include "nic/gpuagent/api/task.hpp"
#include "nic/gpuagent/core/state_base.hpp"
#include "nic/gpuagent/api/aga_state.hpp"

namespace aga {

/// \defgroup AGA_TASK_STATE - task state handling
/// \ingroup AGA
/// @{

/// \brief    state maintained for tasks
class task_state : public state_base {
public:
    /// \brief    constructor
    task_state() {}

    /// \brief    destructor
    ~task_state() {}

    /// \brief    allocate memory required for a task
    /// \return pointer to the allocated task, NULL if no memory
    task *alloc(void) {
        return (task *)SDK_CALLOC(AGA_MEM_ALLOC_TASK, sizeof(task));
    }

    /// \brief      free the given task instance
    /// \param[in]  mapping   pointer to the allocated task instance
    void free(task *task) {
        SDK_FREE(AGA_MEM_ALLOC_TASK, task);
    }

    /// \brief     lookup a task in database given the key
    /// \param[in] key key for the task object
    /// \return    pointer to the task instance found or NULL
    task *find(aga_obj_key_t *key) const {
        return NULL;
    }

    /// \brief API to walk all the db elements
    /// \param[in] walk_cb    callback to be invoked for every node
    /// \param[in] ctxt       opaque context passed back to the callback
    /// \return   SDK_RET_OK on success, failure status code on error
    virtual sdk_ret_t walk(state_walk_cb_t walk_cb, void *ctxt) override {
        return SDK_RET_OK;
    }
};

/// \@}

}    // namespace aga

using aga::task_state;

#endif    // __AGA_TASK_STATE_HPP__
