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
/// smi layer mock API definitions using rocm-smi apis
///
//----------------------------------------------------------------------------

#include "nic/third-party/rocm/rocm_smi_lib/include/rocm_smi/rocm_smi.h"
#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/api/smi/smi.hpp"
#include "nic/gpuagent/api/smi/smi_api_mock_impl.hpp"
#include "nic/gpuagent/api/smi/rocmsmi/smi_utils.hpp"

/// global variables
static const uint64_t g_mock_unique_id[AGA_MOCK_NUM_GPU] = {
    0x82d0655d514f2a30,
    0xb0a8e71cda21053d,
    0xf995d85297ccd9dc,
    0x68cccfa2b07a7844,
    0x5c7d5bf36c641653,
    0x66a63cfe0171bbf6,
    0x2ec4a124a4fbcc4e,
    0x77e5e048b6a83187,
    0xf09b845d31ae3857,
    0x3157ecb6077a5d44,
    0x4c084d1f803abfe4,
    0xfca7aec17c68886b,
    0x75da07dd38df86d0,
    0x3d8f866be4a9c06f,
    0xc2ba04903dff37d3,
    0x6971c8479bd8510f
};

namespace aga {

aga_gpu_handle_t
event_buffer_get_gpu_handle (void *event_buffer_, uint32_t event_idx)
{
    rsmi_evt_notification_data_t *event_buffer;

    event_buffer = (rsmi_evt_notification_data_t *)event_buffer_;
    return event_buffer[event_idx].dv_ind;
}

aga_event_id_t
event_buffer_get_event_id (void *event_buffer_, uint32_t event_idx)
{
    rsmi_evt_notification_data_t *event_buffer;

    event_buffer = (rsmi_evt_notification_data_t *)event_buffer_;
    return aga_event_id_from_smi_event_id(event_buffer[event_idx].event);
}

char *
event_buffer_get_message (void *event_buffer_, uint32_t event_idx)
{
    rsmi_evt_notification_data_t *event_buffer;

    event_buffer = (rsmi_evt_notification_data_t *)event_buffer_;
    return event_buffer[event_idx].message;
}

aga_gpu_handle_t
gpu_get_handle (uint32_t gpu_idx)
{
    return gpu_idx;
}

uint64_t
gpu_get_unique_id (uint32_t gpu_idx)
{
    return g_mock_unique_id[gpu_idx];
}

void *
event_get (void)
{
    static rsmi_evt_notification_data_t event_ntfn_data;
    static uint8_t dev = 0;

    event_ntfn_data.dv_ind = dev % AGA_MOCK_NUM_GPU;
    switch (dev%4) {
    case 0:
        event_ntfn_data.event = RSMI_EVT_NOTIF_GPU_POST_RESET;
        break;
    case 1:
        event_ntfn_data.event = RSMI_EVT_NOTIF_GPU_PRE_RESET;
        break;
    case 2:
        event_ntfn_data.event = RSMI_EVT_NOTIF_THERMAL_THROTTLE;
        break;
    case 3:
        event_ntfn_data.event = RSMI_EVT_NOTIF_VMFAULT;
        break;
    default:
        break;
    }
    strncpy(event_ntfn_data.message, "test event",
            MAX_EVENT_NOTIFICATION_MSG_SIZE);
    dev++;

    return &event_ntfn_data;
}

}    // namespace aga
