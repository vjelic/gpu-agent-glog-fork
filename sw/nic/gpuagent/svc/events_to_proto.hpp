
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
/// This module defines protobuf conversion APIs for events
///
//----------------------------------------------------------------------------

#ifndef __AGA_SVC_EVENTS_TO_PROTO_HPP__
#define __AGA_SVC_EVENTS_TO_PROTO_HPP__

#include "nic/gpuagent/svc/events.hpp"
#include "nic/gpuagent/api/include/base.hpp"
#include "nic/gpuagent/api/include/aga_event.hpp"

sdk_ret_t
aga_event_api_spec_to_proto (amdgpu::Event *proto_event,
                             const aga_event_t *event)
{
    switch (event->id) {
    case AGA_EVENT_ID_VM_PAGE_FAULT:
        proto_event->set_id(amdgpu::EVENT_ID_VM_PAGE_FAULT);
        proto_event->set_category(amdgpu::EVENT_CATEGORY_NONE);
        proto_event->set_severity(amdgpu::EVENT_SEVERITY_DEBUG);
        break;
    case AGA_EVENT_ID_THERMAL_THROTTLE:
        proto_event->set_id(amdgpu::EVENT_ID_THERMAL_THROTTLE);
        proto_event->set_category(amdgpu::EVENT_CATEGORY_NONE);
        proto_event->set_severity(amdgpu::EVENT_SEVERITY_INFO);
        break;
    case AGA_EVENT_ID_GPU_PRE_RESET:
        proto_event->set_id(amdgpu::EVENT_ID_GPU_PRE_RESET);
        proto_event->set_category(amdgpu::EVENT_CATEGORY_NONE);
        proto_event->set_severity(amdgpu::EVENT_SEVERITY_INFO);
        break;
    case AGA_EVENT_ID_GPU_POST_RESET:
        proto_event->set_id(amdgpu::EVENT_ID_GPU_POST_RESET);
        proto_event->set_category(amdgpu::EVENT_CATEGORY_NONE);
        proto_event->set_severity(amdgpu::EVENT_SEVERITY_INFO);
        break;
    case AGA_EVENT_ID_RING_HANG:
        proto_event->set_id(amdgpu::EVENT_ID_RING_HANG);
        proto_event->set_category(amdgpu::EVENT_CATEGORY_NONE);
        proto_event->set_severity(amdgpu::EVENT_SEVERITY_WARN);
        break;
    default:
        AGA_TRACE_ERR("Ignoring unknown GPU event {}", event->id);
        return SDK_RET_INVALID_ARG;
    }
    auto time_stamp = proto_event->mutable_time();
    time_stamp->set_seconds(event->timestamp.tv_sec);
    time_stamp->set_nanos(event->timestamp.tv_nsec);
    proto_event->set_gpu(event->gpu.id, OBJ_MAX_KEY_LEN);
    proto_event->set_description(event->message);
    return SDK_RET_OK;
}

#endif    // __AGA_SVC_EVENTS_TO_SPEC_HPP__
