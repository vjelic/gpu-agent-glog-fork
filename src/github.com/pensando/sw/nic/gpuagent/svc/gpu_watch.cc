
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

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/svc/utils.hpp"
#include "nic/gpuagent/svc/gpu_watch.hpp"
#include "nic/gpuagent/svc/gpu_watch_svc.hpp"

Status
GPUWatchSvcImpl::GPUWatchCreate(ServerContext *context,
                                const GPUWatchRequest *proto_req,
                                GPUWatchResponse *proto_rsp) {
    sdk_ret_t ret;

    ret = aga_svc_gpu_watch_create(proto_req, proto_rsp);
    proto_rsp->set_apistatus(sdk_ret_to_api_status(ret));
    return Status::OK;
}

Status
GPUWatchSvcImpl::GPUWatchDelete(ServerContext *context,
                                const GPUWatchDeleteRequest *proto_req,
                                GPUWatchDeleteResponse *proto_rsp) {
    sdk_ret_t ret;

    ret = aga_svc_gpu_watch_delete(proto_req, proto_rsp);
    proto_rsp->set_apistatus(sdk_ret_to_api_status(ret));
    return Status::OK;
}

Status
GPUWatchSvcImpl::GPUWatchGet(ServerContext *context,
                             const GPUWatchGetRequest *proto_req,
                             GPUWatchGetResponse *proto_rsp) {
    sdk_ret_t ret;

    ret = aga_svc_gpu_watch_get(proto_req, proto_rsp);
    proto_rsp->set_apistatus(sdk_ret_to_api_status(ret));
    return Status::OK;
}

Status
GPUWatchSvcImpl::GPUWatchSubscribe(ServerContext *context,
                     const GPUWatchSubscribeRequest *proto_req,
                     grpc::ServerWriter<GPUWatch> *writer) {
    sdk_ret_t ret;

    ret = aga_svc_gpu_watch_subscribe(context, proto_req, writer);
    return Status::OK;
}
