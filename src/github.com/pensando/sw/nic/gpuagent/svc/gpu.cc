
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

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/svc/utils.hpp"
#include "nic/gpuagent/svc/gpu.hpp"
#include "nic/gpuagent/svc/gpu_svc.hpp"

Status
GPUSvcImpl::GPUGet(ServerContext *context,
                   const GPUGetRequest *proto_req,
                   GPUGetResponse *proto_rsp) {
    sdk_ret_t ret;

    ret = aga_svc_gpu_get(proto_req, proto_rsp);
    proto_rsp->set_apistatus(sdk_ret_to_api_status(ret));
    proto_rsp->set_errorcode(sdk_ret_to_error_code(ret));
    return Status::OK;
}

Status
GPUSvcImpl::GPUUpdate(ServerContext *context,
                      const GPUUpdateRequest *proto_req,
                      GPUUpdateResponse *proto_rsp) {
    sdk_ret_t ret;

    ret = aga_svc_gpu_update(proto_req, proto_rsp);
    proto_rsp->set_apistatus(sdk_ret_to_api_status(ret));
    proto_rsp->set_errorcode(sdk_ret_to_error_code(ret));
    return Status::OK;
}

Status
GPUSvcImpl::GPUReset(ServerContext *context,
                     const GPUResetRequest *proto_req,
                     GPUResetResponse *proto_rsp) {
    sdk_ret_t ret;

    ret = aga_svc_gpu_reset(proto_req, proto_rsp);
    proto_rsp->set_apistatus(sdk_ret_to_api_status(ret));
    proto_rsp->set_errorcode(sdk_ret_to_error_code(ret));
    return Status::OK;
}

Status
DebugGPUSvcImpl::GPUBadPageGet(ServerContext *context,
                     const GPUBadPageGetRequest *proto_req,
                     grpc::ServerWriter<GPUBadPageGetResponse> *writer) {
    aga_svc_gpu_bad_page_get(proto_req, writer);
    return Status::OK;
}

Status
GPUSvcImpl::GPUComputePartitionSet(ServerContext *context,
                const GPUComputePartitionSetRequest *proto_req,
                GPUComputePartitionSetResponse *proto_rsp) {
    sdk_ret_t ret = SDK_RET_INVALID_OP;

    // TODO uncomment after implementing it
    //ret = aga_svc_gpu_compute_partition_set(proto_req, proto_rsp);
    proto_rsp->set_apistatus(sdk_ret_to_api_status(ret));
    proto_rsp->set_errorcode(sdk_ret_to_error_code(ret));
    return Status::OK;
}

Status
GPUSvcImpl::GPUComputePartitionGet(ServerContext *context,
                const GPUComputePartitionGetRequest *proto_req,
                GPUComputePartitionGetResponse *proto_rsp) {
    sdk_ret_t ret;

    ret = aga_svc_gpu_compute_partition_get(proto_req, proto_rsp);
    proto_rsp->set_apistatus(sdk_ret_to_api_status(ret));
    proto_rsp->set_errorcode(sdk_ret_to_error_code(ret));
    return Status::OK;
}
