
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
/// GPU event internal definitions
///
//----------------------------------------------------------------------------

#ifndef __API_INTERNAL_AGA_EVENT_HPP__
#define __API_INTERNAL_AGA_EVENT_HPP__

#include <vector>
#include "nic/gpuagent/api/include/aga_event.hpp"

using std::vector;

/// \brief  event client context sent from frontend to backend
typedef struct aga_event_client_ctxt_s {
    /// client IP address and port
    std::string client;
    /// client_inactive is set to true by the backend thread when
    /// gRPC client is no longer active
    bool client_inactive;
    /// condition variable the front end gRPC thread is going to wait on
    pthread_cond_t cond;
    /// mutex lock to keep the gRPC thread alive
    pthread_mutex_t lock;
    /// opaque context sent from gRPC thread to backend
    /// NOTE:
    /// gRPC response stream to periodically publish events to
    void *stream;
    /// callback API to notify event to the client stream
    aga_event_cb_t notify_cb;
} aga_event_client_ctxt_t;

/// \brief event subscribe info
typedef struct aga_event_subscribe_args_s {
    /// gRPC client context
    aga_event_client_ctxt_t *client_ctxt;
    /// list of events of interest
    vector<aga_event_id_t> events;
    /// GPU id list;
    vector<uint8_t> gpu_ids;
} aga_event_subscribe_args_t;

typedef struct aga_event_gen_args_s {
    /// list of events of interest
    vector<aga_event_id_t> events;
    /// GPU list;
    vector<uint8_t> gpu_ids;
} aga_event_gen_args_t;

#endif    // __API_INTERNAL_AGA_EVENT_HPP__
