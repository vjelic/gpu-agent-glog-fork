
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
/// this file contains agent's API params definition
///
//----------------------------------------------------------------------------

#include "nic/gpuagent/core/api_params.hpp"
#include "nic/gpuagent/core/api_ctxt.hpp"
#include "nic/gpuagent/api/include/aga_gpu.hpp"
#include "nic/gpuagent/api/include/aga_task.hpp"
#include "nic/gpuagent/api/include/aga_gpu_watch.hpp"

#ifndef __INTERNAL_AGA_API_PARAMS_HPP__
#define __INTERNAL_AGA_API_PARAMS_HPP__

namespace aga {

/// \brief API specific parameters
class aga_api_params : public api_params_base {
public:
    /// \brief constructor
    aga_api_params() {};
    /// \brief destructor
    ~aga_api_params() {};
    /// \brief    return reference to the object key
    /// param[in] obj_id    object id/type
    /// param[in] api_op    API operation being performed
    /// \return reference to the object's key
    virtual const aga_obj_key_t& obj_key(obj_id_t obj_id,
                                         api_op_t api_op) override;

public:
    // all object specs
    union {
        aga_obj_key_t key;
        aga_gpu_spec_t gpu_spec;
        aga_task_spec_t task_spec;
        aga_gpu_watch_spec_t gpu_watch_spec;
    };
};

}    // namespage aga

using aga::aga_api_params;

#define AGA_API_PARAMS_FROM_API_CTXT(_api_ctxt_)                   \
            ((aga_api_params *)((_api_ctxt_)->api_params))
#define AGA_GPU_SPEC(_api_params_)                                 \
            &(((aga_api_params *)(_api_params_))->gpu_spec);
#define AGA_TASK_SPEC(_api_params_)                                \
            &(((aga_api_params *)(_api_params_))->task_spec);
#define AGA_GPU_WATCH_SPEC(_api_params_)                           \
            &(((aga_api_params *)(_api_params_))->gpu_watch_spec);

#endif    // __INTERNAL_AGA_API_PARAMS_HPP__
