
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
/// This module defines protobuf conversion APIs for device topology object
///
//----------------------------------------------------------------------------

#ifndef __AGA_SVC_TOPO_TO_PROTO_HPP__
#define __AGA_SVC_TOPO_TO_PROTO_HPP__

#include <string>
#include "nic/gpuagent/svc/topo.hpp"
#include "nic/gpuagent/api/include/aga_gpu.hpp"

static inline amdgpu::DeviceType
aga_device_type_to_proto (aga_device_type_t type)
{
    switch (type) {
    case AGA_DEVICE_TYPE_GPU:
        return amdgpu::DEVICE_TYPE_GPU;
    default:
        return amdgpu::DEVICE_TYPE_NONE;
    }
}

static inline amdgpu::IOLinkType
aga_io_link_type_to_proto (aga_io_link_type_t type)
{
    switch (type) {
    case AGA_IO_LINK_TYPE_PCIE:
        return amdgpu::IO_LINK_TYPE_PCIE;
    case AGA_IO_LINK_TYPE_XGMI:
        return amdgpu::IO_LINK_TYPE_XGMI;
    default:
        return amdgpu::IO_LINK_TYPE_NONE;
    }
}

// populate proto buf from device topology info
static inline void
aga_device_topology_api_info_to_proto (aga_device_topology_info_t *info,
                                       void *ctxt)
{
    DeviceTopologyGetResponse *proto_rsp = (DeviceTopologyGetResponse *)ctxt;
    auto topo = proto_rsp->add_devicetopology();
    auto device = topo->mutable_device();

    device->set_type(aga_device_type_to_proto(info->device.type));
    device->set_name(info->device.name);

    for (uint32_t i = 0; i < AGA_MAX_PEER_DEVICE; i++) {
        auto peer_info = &info->peer_device[i];
        if (!peer_info->valid) {
            break;
        }
        auto peer_device = topo->add_peerdevice();
        peer_device->mutable_peerdevice()->set_type(
                         aga_device_type_to_proto(peer_info->peer_device.type));
        peer_device->mutable_peerdevice()->set_name(
                         peer_info->peer_device.name);
        peer_device->mutable_connection()->set_type(
                         aga_io_link_type_to_proto(peer_info->connection.type));
        peer_device->set_numhops(peer_info->num_hops);
        peer_device->set_weight(peer_info->link_weight);
    }
}

#endif    // __AGA_SVC_TOPO_TO_PROTO_HPP__
