

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

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/svc/utils.hpp"
#include "nic/gpuagent/svc/topo.hpp"
#include "nic/gpuagent/svc/topo_svc.hpp"

Status
TopoSvcImpl::DeviceTopologyGet(ServerContext *context,
                               const DeviceTopologyGetRequest *proto_req,
                               DeviceTopologyGetResponse *proto_rsp) {
    sdk_ret_t ret;

    ret = aga_svc_device_topology_get(proto_req, proto_rsp);
    proto_rsp->set_apistatus(sdk_ret_to_api_status(ret));
    proto_rsp->set_errorcode(sdk_ret_to_error_code(ret));
    return Status::OK;
}
