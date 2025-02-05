
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
/// init time APIs for agent
///
//----------------------------------------------------------------------------

#ifndef __AGA_INIT_HPP__
#define __AGA_INIT_HPP__

#include <string>
#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/api/include/aga_event.hpp"
#include "nic/gpuagent/api/internal/aga_event.hpp"

/// \defgroup AGA_INIT initialization APIs
/// @{

/// \brief initialization parameters
typedef struct aga_init_params_s {
    // gRPC server (IP:port)
    std::string grpc_server;
    // rdcd gRPC server (IP:port) to connect to
    std::string rdc_server;
} aga_init_params_t;

/// \brief    initialize the agent state, threads etc.
/// \param[in] init_params    init time parameters
/// \return     SDK_RET_OK or error status in case of failure
sdk_ret_t aga_init(aga_init_params_t *init_params);

#endif    // __AGA_INIT_HPP__
