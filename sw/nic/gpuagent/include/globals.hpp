
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
/// agent header file
///
//----------------------------------------------------------------------------

#ifndef _AGA_INCLUDE_GLOBALS_HPP__
#define _AGA_INCLUDE_GLOBALS_HPP__

#include "nic/sdk/include/sdk/globals.hpp"

/// GPU agent external gRPC port
#define AGA_DEFAULT_GRPC_SERVER_PORT          50061
/// rdcd gRPC port gpuagent uses for communication
#define AGA_DEFAULT_RDC_GRPC_SERVER_PORT      50051
/// initial delay after which the heart beat punching starts
#define AGA_HEARTBEAT_PUNCH_START_DELAY       10.0
/// heart beat punching timeout in seconds
#define AGA_HEARTBEAT_PUNCH_TIMEOUT           1.0
/// max. number of grpc threads
#define AGA_MAX_GRPC_THREADS                  256

/// thread ids
/// [AGA_THREAD_ID_MIN - AGA_THREAD_ID_MAX] are for gpuagent threads
/// [AGA_AGENT_THREAD_ID_MIN - AGA_AGENT_THREAD_ID_MAX] are for gpu agent layer
/// threads IPC endpoints internal to gpuagent use their unique thread ids
/// as their IPC (client/server) identifier. so reserving the thread ids from
/// IPC ids
typedef enum aga_thread_id_s {
    AGA_THREAD_ID_MIN       = (SDK_IPC_ID_MAX + 1),
    AGA_THREAD_ID_MAX       = (AGA_THREAD_ID_MIN + 31),
    AGA_AGENT_THREAD_ID_MIN = (AGA_THREAD_ID_MAX + 1),
    AGA_AGENT_THREAD_ID_MAX = (AGA_AGENT_THREAD_ID_MIN + 7),
} aga_thread_id_t;

/// \brief    IPC message identifier carving
enum {
    AGA_IPC_MSG_ID_MIN = SDK_IPC_MSG_ID_MAX + 1,
    AGA_IPC_MSG_ID_MAX = AGA_IPC_MSG_ID_MIN + 8
};

#endif    // _AGA_INCLUDE_GLOBALS_HPP__
