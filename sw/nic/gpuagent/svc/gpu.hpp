
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
/// class that implements APIs in GPUSvc
///
//----------------------------------------------------------------------------

#ifndef __AGA_SVC_GPU_HPP__
#define __AGA_SVC_GPU_HPP__

#include "grpc++/grpc++.h"
#include "gen/proto/gpuagent/types.pb.h"
#include "gen/proto/gpuagent/gpu.pb.h"
#include "gen/proto/gpuagent/gpu.grpc.pb.h"

using grpc::Status;
using grpc::ServerContext;

using types::Empty;
using amdgpu::GPUSvc;
using amdgpu::GPUGetRequest;
using amdgpu::GPUGetResponse;
using amdgpu::GPUSpec;
using amdgpu::GPUStatus;
using amdgpu::GPUStats;
using amdgpu::GPUUpdateRequest;
using amdgpu::GPUUpdateResponse;
using amdgpu::GPUResetRequest;
using amdgpu::GPUResetResponse;
using amdgpu::GPUPCIeStatus;
using amdgpu::GPUPCIeStats;
using amdgpu::GPUVoltage;
using amdgpu::GPUMemoryUsage;
using amdgpu::GPUUsage;
using amdgpu::GPUVRAMStatus;
using amdgpu::GPUVRAMUsage;
using amdgpu::GPUClockFrequencyRange;
using amdgpu::DebugGPUSvc;
using amdgpu::GPUBadPageGetRequest;
using amdgpu::GPUBadPageGetResponse;
using amdgpu::GPUComputePartitionSetRequest;
using amdgpu::GPUComputePartitionSetResponse;
using amdgpu::GPUComputePartitionGetRequest;
using amdgpu::GPUComputePartitionGetResponse;

class GPUSvcImpl final : public GPUSvc::Service {
public:
    Status GPUGet(ServerContext *context,
                  const GPUGetRequest *proto_req,
                  GPUGetResponse *proto_rsp) override;
    Status GPUUpdate(ServerContext *context,
                     const GPUUpdateRequest *proto_req,
                     GPUUpdateResponse *proto_rsp) override;
    Status GPUReset(ServerContext *context,
                    const GPUResetRequest *proto_req,
                    GPUResetResponse *proto_rsp) override;
    Status GPUComputePartitionSet(ServerContext *context,
               const GPUComputePartitionSetRequest *proto_req,
               GPUComputePartitionSetResponse *proto_rsp) override;
    Status GPUComputePartitionGet(ServerContext *context,
               const GPUComputePartitionGetRequest *proto_req,
               GPUComputePartitionGetResponse *proto_rsp) override;
};

class DebugGPUSvcImpl final : public DebugGPUSvc::Service {
public:
    Status GPUBadPageGet(ServerContext *context,
               const GPUBadPageGetRequest *proto_req,
               grpc::ServerWriter<GPUBadPageGetResponse> *writer) override;
};

#endif    // __AGA_SVC_GPU_HPP__
