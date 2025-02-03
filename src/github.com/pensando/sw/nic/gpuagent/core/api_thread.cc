
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
/// API thread specific helper functions
///
//----------------------------------------------------------------------------

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/sdk/lib/ipc/ipc.hpp"
#include "nic/sdk/lib/event_thread/event_thread.hpp"
#include "nic/gpuagent/include/globals.hpp"
#include "nic/gpuagent/core/trace.hpp"
#include "nic/gpuagent/core/aga_core.hpp"
#include "nic/gpuagent/core/api_msg.hpp"
#include "nic/gpuagent/core/api_msg.hpp"
#include "nic/gpuagent/core/api_thread.hpp"
#include "nic/gpuagent/core/api_engine.hpp"
#include "nic/gpuagent/core/state_base.hpp"

namespace event = sdk::event_thread;

namespace aga {

static void
api_thread_heartbeat_punch_cb (event::timer_t *timer)
{
    static sdk::lib::thread *curr_thread = sdk::lib::thread::current_thread();
    curr_thread->punch_heartbeat();
}

static void
api_thread_ipc_msg_cb (sdk::ipc::ipc_msg_ptr msg, const void *ctxt)
{
    sdk_ret_t ret;
    api_msg_t *api_msg = *(api_msg_t **)msg->data();

    AGA_TRACE_DEBUG("Rcvd API IPC msg");
    // basic validation
    assert(likely(api_msg != NULL));
    assert(likely(api_msg->msg_id == AGA_IPC_MSG_ID_CFG));
    ret = api_msg_handle_cb(api_msg, msg);
    sdk::ipc::respond(msg, &ret, sizeof(ret));
}

void
api_thread_init_fn (void *ctxt)
{
    sdk_ret_t ret;
    static event::timer_t hb_timer;
    sdk::lib::thread *curr_thread = (sdk::lib::thread *)ctxt;
    state_base *state = (state_base *)curr_thread->data();

    api_engine_init(state);
    sdk::ipc::reg_request_handler(AGA_IPC_MSG_ID_CFG,
                                  api_thread_ipc_msg_cb, NULL);
    // start heartbeat timer
    event::timer_init(&hb_timer, api_thread_heartbeat_punch_cb,
                      AGA_HEARTBEAT_PUNCH_START_DELAY,
                      AGA_HEARTBEAT_PUNCH_TIMEOUT);
    event::timer_start(&hb_timer);
}

void
api_thread_exit_fn (void *ctxt)
{
}

void
api_thread_event_cb (void *msg, void *ctxt)
{
}

bool
is_api_thread_ready (void) {
    auto thr = sdk::lib::thread::find(AGA_THREAD_ID_API);
    return (thr && thr->ready());
}

sdk_ret_t
spawn_api_thread (state_base *state)
{
    sdk::event_thread::event_thread *new_thread;

    new_thread =
        sdk::event_thread::event_thread::factory(
            "api", AGA_THREAD_ID_API,
            sdk::lib::THREAD_ROLE_CONTROL,
            0x0,    // use all control cores
            api_thread_init_fn,
            api_thread_exit_fn,
            api_thread_event_cb,
            sdk::lib::thread::priority_by_role(sdk::lib::THREAD_ROLE_CONTROL),
            sdk::lib::thread::sched_policy_by_role(sdk::lib::THREAD_ROLE_CONTROL),
            THREAD_YIELD_ENABLE);
     SDK_ASSERT_TRACE_RETURN((new_thread != NULL), SDK_RET_ERR,
                             "API thread create failure");
     new_thread->set_data(state);
     new_thread->start(new_thread);
     return SDK_RET_OK;
}

}    // namespace aga
