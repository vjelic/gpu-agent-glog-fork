
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
/// class that implements APIs in DebugSvc
///
//----------------------------------------------------------------------------


#ifndef __AGA_SVC_DEBUG_HPP__
#define __AGA_SVC_DEBUG_HPP__

#include "grpc++/grpc++.h"
#include "gen/proto/gpuagent/types.pb.h"
#include "gen/proto/gpuagent/debug.grpc.pb.h"

using grpc::Status;
using grpc::ServerContext;

using amdgpu::DebugSvc;
using types::Empty;
using amdgpu::TraceRequest;
using amdgpu::TraceResponse;
using amdgpu::TraceGetResponse;

class DebugSvcImpl final : public DebugSvc::Service {
public:
    Status TraceUpdate(ServerContext *context, const TraceRequest *req,
                       TraceResponse *rsp) override;
    Status TraceGet(ServerContext *context, const Empty *req,
                         TraceGetResponse *rsp) override;
    Status TraceFlush(ServerContext *context, const Empty *req,
                      Empty *rsp) override;
};

#endif    // __AGA_SVC_DEBUG_HPP__
