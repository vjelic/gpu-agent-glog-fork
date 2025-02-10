
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
/// IPC message identifiers
///
//----------------------------------------------------------------------------

#ifndef __AGA_CORE_IPC_MSG_HPP__
#define __AGA_CORE_IPC_MSG_HPP__

#include "nic/gpuagent/include/globals.hpp"

namespace aga {

typedef enum aga_ipc_msg_id_e {
    /// IPC msg to API thread
    AGA_IPC_MSG_ID_CFG = AGA_IPC_MSG_ID_MIN,
    /// IPC msg for event subscription
    AGA_IPC_MSG_ID_EVENT_SUBSCRIBE,
    /// IPC msg for GPU watch subscription
    AGA_IPC_MSG_ID_GPU_WATCH_SUBSCRIBE,
    /// IPC msg for event generation
    AGA_IPC_MSG_ID_EVENT_GEN,
} aga_ipc_msg_id_t;

}    // namespace aga

using aga::aga_ipc_msg_id_t;

#endif    // __AGA_CORE_IPC_MSG_HPP__
