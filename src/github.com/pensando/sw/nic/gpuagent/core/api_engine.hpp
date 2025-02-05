
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
/// API processing framework/engine functionality
///
//----------------------------------------------------------------------------

#ifndef __AGA_CORE_API_ENGINER_HPP__
#define __AGA_CORE_API_ENGINER_HPP__

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/core/api_ctxt.hpp"
#include "nic/gpuagent/core/state_base.hpp"

using sdk::ipc::ipc_msg_ptr;

namespace aga {

/// \brief    initialize the API engine
/// \param[in] state    pointer to application specific state (base) class
///                     instance
/// \return #SDK_RET_OK on success, failure status code on error
sdk_ret_t api_engine_init(state_base *state);

/// \brief    handle the incoming API message
/// \param[in] api_msg    API msg received
/// \param[in] ipc_msg    IPC msg received that contains the API context(s)
/// \return #SDK_RET_OK on success, failure status code on error
sdk_ret_t api_msg_handle_cb(api_msg_t *api_msg, sdk::ipc::ipc_msg_ptr ipc_msg);

}    // namespace aga

#endif    //  __AGA_CORE_API_ENGINER_HPP__
