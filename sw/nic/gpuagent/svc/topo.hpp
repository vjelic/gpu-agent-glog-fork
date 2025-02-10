

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
/// class that implements APIs in TopoSvc
///
//----------------------------------------------------------------------------

#ifndef __AGA_SVC_TOPO_HPP__
#define __AGA_SVC_TOPO_HPP__

#include "grpc++/grpc++.h"
#include "gen/proto/gpuagent/types.pb.h"
#include "gen/proto/gpuagent/topo.pb.h"
#include "gen/proto/gpuagent/topo.grpc.pb.h"

using grpc::Status;
using grpc::ServerContext;

using types::Empty;
using amdgpu::TopoSvc;
using amdgpu::DeviceTopologyGetRequest;
using amdgpu::DeviceTopologyGetResponse;
using amdgpu::DeviceConnection;
using amdgpu::Device;
using amdgpu::PeerDevice;
using amdgpu::DeviceTopology;

class TopoSvcImpl final : public TopoSvc::Service {
public:
    Status DeviceTopologyGet(ServerContext *context,
                             const DeviceTopologyGetRequest *proto_req,
                             DeviceTopologyGetResponse *proto_rsp) override;
};

#endif    // __AGA_SVC_TOPO_HPP__
