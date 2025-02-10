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


//-----------------------------------------------------------------------------

//
// periodic thread manages few timer wheels and can carry our periodic tasks
// as background activities. Few examples include:
// - delay deleting memory resources to slabs or heap
// - flow table scan to age out sessions or detect dead flows
// - periodic stats collection and/or aggregation
//------------------------------------------------------------------------------

#ifndef __PERIODIC_HPP__
#define __PERIODIC_HPP__

#include "include/sdk/base.hpp"
#include "lib/twheel/twheel.hpp"

namespace sdk {
namespace lib {

//------------------------------------------------------------------------------
// return true if periodic thread is up and running
//------------------------------------------------------------------------------
bool periodic_thread_is_running(void);

//------------------------------------------------------------------------------
// return true if periodic thread is ready and fully initialized
//------------------------------------------------------------------------------
bool periodic_thread_is_ready(void);

//------------------------------------------------------------------------------
// one time initialization for periodic thread
//------------------------------------------------------------------------------
void *periodic_thread_init(void *ctxt);

//------------------------------------------------------------------------------
// core logic of periodic thread
//------------------------------------------------------------------------------
void *periodic_thread_run(void *ctxt);

//------------------------------------------------------------------------------
// cleanup for periodic thread
//------------------------------------------------------------------------------
void periodic_thread_cleanup(void *arg=NULL);

//------------------------------------------------------------------------------
// spawn a periodic thread that is an event thread
//------------------------------------------------------------------------------
sdk_ret_t spawn_periodic_event_thread(void *ctxt);

//------------------------------------------------------------------------------
// send an indication to stop the periodic thread
//------------------------------------------------------------------------------
void periodic_ev_thread_stop(void);

//------------------------------------------------------------------------------
// wait for the periodic event thread to stop
//------------------------------------------------------------------------------
void periodic_ev_thread_wait(void);

//------------------------------------------------------------------------------
// API invoked by other threads to trigger cb after timeout
// Returns the timer entry used to update/delete the timer
//------------------------------------------------------------------------------
void *timer_schedule(uint32_t timer_id, uint64_t timeout, void *ctxt,
                     sdk::lib::twheel_cb_t cb, bool periodic,
                     uint64_t initial_delay = 0);

//------------------------------------------------------------------------------
// API invoked by other threads to get timeout remaining in msecs for the timer.
//------------------------------------------------------------------------------
uint64_t get_timeout_remaining(void *timer);

//------------------------------------------------------------------------------
// API invoked by other threads to delete the scheduled timer
//------------------------------------------------------------------------------
void *timer_delete(void *timer);

//------------------------------------------------------------------------------
// API invoked by other threads to update the scheduled timer context
//------------------------------------------------------------------------------
void *timer_update_ctxt(void *timer, void *ctxt);

//------------------------------------------------------------------------------
// API invoked by other threads to update the scheduled timer
//------------------------------------------------------------------------------
void *timer_update(void *timer, uint64_t timeout, bool periodic, void *ctxt);

}    // namespace lib
}    // namespace sdk

#endif    // __PERIODIC_HPP__

