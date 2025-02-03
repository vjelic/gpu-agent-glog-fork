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
/// smi layer mock impl APIs
///
//----------------------------------------------------------------------------

#ifndef __AGA_API_SMI_API_MOCK_IMPL_HPP__
#define __AGA_API_SMI_API_MOCK_IMPL_HPP__

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/api/include/aga_event.hpp"
#include "nic/gpuagent/api/smi/smi.hpp"

#define AGA_MOCK_NUM_GPU    16

namespace aga {

/// \brief      function to get GPU handle from event buffer
/// \param[in]  event_buffer    event buffer
/// \param[in]  event_idx       event index
/// \return     GPU handle
aga_gpu_handle_t event_buffer_get_gpu_handle(void *event_buffer,
                                             uint32_t event_idx);

/// \brief      function to get event identifier from event buffer
/// \param[in]  event_buffer    event buffer
/// \param[in]  event_idx       event index
/// \return     event identifier
aga_event_id_t event_buffer_get_event_id(void *event_buffer,
                                         uint32_t event_idx);

/// \brief      function to get event message from event buffer
/// \param[in]  event_buffer    event buffer
/// \param[in]  event_idx       event index
/// \return     event identifier
char *event_buffer_get_message(void *event_buffer, uint32_t event_idx);

/// \brief      get GPU handle given linear GPU index
/// \param[in]  gpu_idx         linear GPU index
/// return      GPU handle
aga_gpu_handle_t gpu_get_handle(uint32_t gpu_idx);

/// \brief      get GPU unique identifier given linear GPU index
/// \param[in]  gpu_idx         linear GPU index
/// return      GPU unique identifier
uint64_t gpu_get_unique_id(uint32_t gpu_idx);

/// \brief      get GPU event
/// return      pointer to event
void *event_get(void);

}    // namespace aga

#endif    // __AGA_API_SMI_API_HPP__
