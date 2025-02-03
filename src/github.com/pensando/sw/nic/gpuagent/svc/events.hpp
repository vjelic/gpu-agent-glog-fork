
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
/// This file implements APIs EventSvc
///
//----------------------------------------------------------------------------

#ifndef __AGA_SVC_EVENTS_HPP__
#define __AGA_SVC_EVENTS_HPP__

#include "grpc++/grpc++.h"
#include "gen/proto/gpuagent/types.pb.h"
#include "gen/proto/gpuagent/events.pb.h"
#include "gen/proto/gpuagent/events.grpc.pb.h"

using grpc::Status;
using grpc::ServerContext;
using grpc::ServerWriter;

using amdgpu::EventSvc;
using amdgpu::Event;
using amdgpu::EventSubscribeRequest;
using amdgpu::EventRequest;
using amdgpu::EventResponse;
using amdgpu::DebugEventSvc;
using amdgpu::EventGenRequest;
using amdgpu::EventGenResponse;

class EventSvcImpl final : public EventSvc::Service {
public:
    Status EventGet(ServerContext* context,
                    const EventRequest *request,
                    EventResponse *response) override;
    Status EventSubscribe(ServerContext* context,
                          const EventSubscribeRequest *request,
                          ServerWriter<Event> *stream) override;
};

class DebugEventSvcImpl final : public DebugEventSvc::Service {
public:
    Status EventGen(ServerContext* context,
                    const EventGenRequest *request,
                    EventGenResponse *response) override;
};

#endif    // __AGA_SVC_EVENTS_HPP__
