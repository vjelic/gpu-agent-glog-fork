
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
/// API thread specific helper functions
///
//----------------------------------------------------------------------------

#ifndef __AGA_CORE_API_THREAD_HPP__
#define __AGA_CORE_API_THREAD_HPP__

#include "nic/sdk/lib/ipc/ipc.hpp"
#include "nic/gpuagent/core/state_base.hpp"

namespace aga {

/// \defgroup AGA_API_THREAD API thread helper functions/wrappers
/// @{

/// \brief    callback function invoked during api thread initialization
/// \param[in] ctxt    opaque context
void api_thread_init_fn(void *ctxt);

/// \brief    callback function invoked during api thread exit
/// \param[in] ctxt    opaque context
void api_thread_exit_fn(void *ctxt);

/// \brief    callback function invoked to process events received by API thread
/// \param[in] msg     message carrying the event information
/// \param[in] ctxt    opaque context
void api_thread_event_cb(void *msg, void *ctx);

/// \brief    return true if API thread is ready to receive events
/// \return true or false based on whether API thread is ready or not
bool is_api_thread_ready(void);

/// \brief    spawn the API thread
/// \param[in] state    agent state instance
/// \return SDK_RET_OK or error code in case of failure
sdk_ret_t spawn_api_thread(state_base *state);

/// \@}

}    // namespace aga

#endif    // __AGA_CORE_API_THREAD_HPP__
