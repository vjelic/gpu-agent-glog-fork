
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
/// class that implements APIs in GPUWatchSvc
///
//----------------------------------------------------------------------------

#ifndef __AGA_SVC_GPU_WATCH_HPP__
#define __AGA_SVC_GPU_WATCH_HPP__

#include "grpc++/grpc++.h"
#include "gen/proto/gpuagent/types.pb.h"
#include "gen/proto/gpuagent/gpu_watch.pb.h"
#include "gen/proto/gpuagent/gpu_watch.grpc.pb.h"

using grpc::Status;
using grpc::ServerContext;

using types::Empty;
using amdgpu::GPUWatchAttrId;
using amdgpu::GPUWatchSvc;
using amdgpu::GPUWatchSpec;
using amdgpu::GPUWatchStatus;
using amdgpu::GPUWatchStats;
using amdgpu::GPUWatchRequest;
using amdgpu::GPUWatchResponse;
using amdgpu::GPUWatchDeleteRequest;
using amdgpu::GPUWatchDeleteResponse;
using amdgpu::GPUWatchGetRequest;
using amdgpu::GPUWatchGetResponse;
using amdgpu::GPUWatchSubscribeRequest;
using amdgpu::GPUWatch;

class GPUWatchSvcImpl final : public GPUWatchSvc::Service {
public:
    Status GPUWatchCreate(ServerContext *context,
                          const GPUWatchRequest *proto_req,
                          GPUWatchResponse *proto_rsp) override;
    Status GPUWatchDelete(ServerContext *context,
                          const GPUWatchDeleteRequest *proto_req,
                          GPUWatchDeleteResponse *proto_rsp) override;
    Status GPUWatchGet(ServerContext *context,
                       const GPUWatchGetRequest *proto_req,
                       GPUWatchGetResponse *proto_rsp) override;
    Status GPUWatchSubscribe(ServerContext *context,
               const GPUWatchSubscribeRequest *proto_req,
               grpc::ServerWriter<GPUWatch> *writer) override;
};

#endif    // __AGA_SVC_GPU_WATCH_HPP__
