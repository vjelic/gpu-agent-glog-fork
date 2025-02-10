
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
/// svc layer helper functions
///
//----------------------------------------------------------------------------

#ifndef __AGA_SVC_UTILS_HPP__
#define __AGA_SVC_UTILS_HPP__

using std::string;

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/api/include/base.hpp"
#include "gen/proto/gpuagent/types.pb.h"

// maximum number of records in a streaming response message
#define AGA_MAX_STREAMING_RSP_SIZE      (500)

/// context used during streaming get operations to communicate
/// requirements between svc and api layers
typedef struct streaming_get_ctxt_s {
    /// proto msg ctxt
    void *msg_ctxt;
    /// streaming writer ctxt
    void *writer_ctxt;
    /// count of objects matching the get request
    uint8_t count;
} streaming_get_ctxt_t;

static inline sdk_ret_t
aga_obj_key_proto_to_api_spec (aga_obj_key_t *api_spec,
                               const ::std::string& proto_key)
{
    if (proto_key.length() > OBJ_MAX_KEY_LEN) {
        return SDK_RET_INVALID_ARG;
    }
    // set all the key bytes to 0 1st and hash on the full key can't include
    // uninitialized memory
    memset(api_spec->id, 0, sizeof(api_spec->id));
    // set the key bytes
    memcpy(api_spec->id, proto_key.data(),
           SDK_MIN(proto_key.length(), OBJ_MAX_KEY_LEN));
    return SDK_RET_OK;
}

static inline types::ApiStatus
sdk_ret_to_api_status (sdk_ret_t ret)
{
    switch (ret()) {
    case SDK_RET_OK:
        return types::ApiStatus::API_STATUS_OK;
    case SDK_RET_ERR:
        return types::ApiStatus::API_STATUS_ERR;
    case SDK_RET_INVALID_ARG:
        return types::ApiStatus::API_STATUS_INVALID_ARG;
    case SDK_RET_ENTRY_EXISTS:
        return types::ApiStatus::API_STATUS_EXISTS_ALREADY;
    case SDK_RET_OOM:
        return types::ApiStatus::API_STATUS_OUT_OF_MEM;
    case SDK_RET_ENTRY_NOT_FOUND:
        return types::ApiStatus::API_STATUS_NOT_FOUND;
    case SDK_RET_INVALID_OP:
        return types::ApiStatus::API_STATUS_OPERATION_NOT_ALLOWED;
    case SDK_RET_OP_NOT_SUPPORTED:
        return types::ApiStatus::API_STATUS_OPERATION_NOT_SUPPORTED;
    case SDK_RET_IN_USE:
        return types::ApiStatus::API_STATUS_IN_USE;
    default:
        break;
    }
    return types::ApiStatus::API_STATUS_ERR;
}

static inline types::ErrorCode
sdk_ret_to_error_code (sdk_ret_t ret)
{
    switch (ret()) {
    case SDK_RET_OK:
        return types::ErrorCode::ERR_CODE_NONE;
    default:
        break;
    }
    switch (ret.err_code()) {
    case ERR_CODE_NONE:
        return types::ErrorCode::ERR_CODE_NONE;

    // GPU object specific error codes
    case ERR_CODE_GPU_CLOCK_FREQ_RANGE_INVALID:
        return types::ErrorCode::ERR_CODE_GPU_CLOCK_FREQ_RANGE_INVALID;
    case ERR_CODE_GPU_OVERDRIVE_OUT_OF_RANGE:
        return types::ErrorCode::ERR_CODE_GPU_OVERDRIVE_OUT_OF_RANGE;
    case ERR_CODE_GPU_NUM_CLOCK_FREQ_RANGE_EXCEEDED:
        return types::ErrorCode::ERR_CODE_GPU_NUM_CLOCK_FREQ_RANGE_EXCEEDED;
    case ERR_CODE_GPU_DUPLICATE_CLOCK_FREQ_RANGE:
        return types::ErrorCode::ERR_CODE_GPU_DUPLICATE_CLOCK_FREQ_RANGE;
    case ERR_CODE_GPU_CLOCK_TYPE_FREQ_RANGE_UPDATE_NOT_SUPPORTED:
        return types::ErrorCode::
            ERR_CODE_GPU_CLOCK_TYPE_FREQ_RANGE_UPDATE_NOT_SUPPORTED;

    // smi layer object specific error codes
    case ERR_CODE_SMI_GPU_POWER_CAP_OUT_OF_RANGE:
        return types::ErrorCode::ERR_CODE_SMI_GPU_POWER_CAP_OUT_OF_RANGE;

    // catch all error code
    default:
        return types::ErrorCode::ERR_CODE_UNKNOWN;
    }
}

/// \brief this API is invoked at verbose trace level settings
/// \param[in] obj          name of the object
/// \param[in] operation    API operation
/// \param[in] key          key of the API object
void aga_api_trace_verbose(const char *obj, const char *operation,
                           const google::protobuf::Message *msg);

/// \brief this API is invoked at default trace level settings
/// \param[in] obj          name of the object
/// \param[in] operation    API operation
/// \param[in] key          key of the API object
void aga_api_trace_terse(const char *obj, const char *operation,
                         const char *key);

/// \brief this API is invoked at default trace level settings
/// \param[in] obj          name of the object
/// \param[in] operation    API operation
/// \param[in] proto_msg    protobuf message to be logged
void aga_api_trace_terse(const char *obj, const char *operation,
                         const google::protobuf::Message *msg);

#endif    // __AGA_SVC_UTILS_HPP__
