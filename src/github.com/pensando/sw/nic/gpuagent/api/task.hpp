
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
/// task handling
///
//----------------------------------------------------------------------------

#ifndef __AGA_TASK_HPP__
#define __AGA_TASK_HPP__

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/core/api_base.hpp"
#include "nic/gpuagent/core/api_params.hpp"
#include "nic/gpuagent/api/include/aga_task.hpp"
#include "nic/gpuagent/api/internal/aga_gpu_watch.hpp"

namespace aga {

// forward declaration
class task_state;

/// \defgroup AGA_TASK - task functionality
/// \ingroup AGA
/// @{

/// \brief task object
class task : public api_base {
public:
    /// \brief     factory method to allocate and initialize a task
    /// \param[in] spec tasl specification
    /// \return    new instance of task or NULL, in case of error
    static task *factory(aga_task_spec_t *spec);

    /// \brief     release all the s/w state associate with the given
    ///            task instance
    ///            if any, and free the memory
    /// \param[in] task    task to be freed
    /// \NOTE:     h/w entries should have been cleaned up (by calling
    ///            impl->cleanup_hw() before calling this
    static void destroy(task *task);

    /// \brief    free all the memory associated with this object without
    ///           touching any of the databases or h/w etc.
    /// \param[in] task    task to be freed
    /// \return   SDK_RET_OK or error code
    static sdk_ret_t free(task *task);

    /// \brief initiate delay deletion of this object
    virtual sdk_ret_t delay_delete(void) override;

    /// \brief create handler
    /// \param[in] api_params    API parameters capturing key/spec etc
    /// \return   SDK_RET_OK or error code
    virtual sdk_ret_t create_handler(api_params_base *api_params) override;

    /// \brief return stringified key of the object (for debugging)
    virtual string key2str(void) const override {
        return "task";
    }

    /// \brief  return the key of task
    /// \return key of the task
    virtual const aga_obj_key_t& key(void) const override { return key_; }

private:
    /// \brief constructor
    task() {}

    /// \brief destructor
    ~task() {}

    /// \brief    handle GPU reset task
    /// \param[in] spec    GPU reset task specification
    /// \return   SDK_RET_OK or error code
    sdk_ret_t handle_gpu_reset_task_(aga_gpu_reset_task_spec_t *spec);

    /// \brief    update watch db task
    /// \param[in] watch_db   GPU stats watch db
    /// \return   SDK_RET_OK or error code
    sdk_ret_t handle_gpu_update_watch_db_task_(aga_gpu_watch_db_t *watch_db);

    /// \brief    handle GPU watch subscriber add task
    /// \param[in] spec    GPU watch subscriber spec
    /// \return   SDK_RET_OK or error code
    sdk_ret_t handle_gpu_watch_subscriber_add_task_(
                  aga_gpu_watch_subscriber_spec_t *spec);

    /// \brief    handle GPU watch subscriber delete task
    /// \param[in] spec    GPU watch subscriber spec
    /// \return   SDK_RET_OK or error code
    sdk_ret_t handle_gpu_watch_subscriber_del_task_(
                  aga_gpu_watch_subscriber_spec_t *spec);

private:
    /// key of this object
    aga_obj_key_t key_;

    /// a friend of task object
    friend class task_state;
};

/// \brief    create callback on task object
/// \param[in] api_obj    new object instantiated to handle create operation
/// \param[in] api_params API params containing the context of the API call
/// \return    SDK_RET_OK or error code in case of failure
sdk_ret_t aga_task_create_cb(api_base *api_obj, api_params_base *api_params);

/// \@}

}    // namespace aga

using aga::task;

#endif    // __AGA_TASK_HPP__
