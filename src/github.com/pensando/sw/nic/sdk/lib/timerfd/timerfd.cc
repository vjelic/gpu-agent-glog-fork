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


#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include "include/sdk/timerfd.hpp"
#include "include/sdk/timestamp.hpp"
#include "lib/logger/logger.h"

namespace sdk {
namespace lib {

//------------------------------------------------------------------------------
// initiaize information about a given timer fd
//------------------------------------------------------------------------------
void
timerfd_init (timerfd_info_t *pinfo)
{
    pinfo->timer_fd = -1;
    pinfo->usecs = 0;
    pinfo->missed_wakeups = 0;
}

//------------------------------------------------------------------------------
// create and initialize a timer fd, this fd can then be used
// in poll/select system calls eventually
//------------------------------------------------------------------------------
int
timerfd_prepare (timerfd_info_t *pinfo)
{
    int                  fd;
    struct itimerspec    itspec;
    timespec_t           tspec;

    // create timer fd
    fd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (fd == -1) {
        return fd;
    }
    pinfo->missed_wakeups = 0;
    pinfo->timer_fd = fd;

    // initialize the timeout
    sdk::timestamp_from_nsecs(&tspec, pinfo->usecs * TIME_NSECS_PER_USEC);
    itspec.it_interval = tspec;
    itspec.it_value = tspec;
    return timerfd_settime(fd, 0, &itspec, NULL);
}

//------------------------------------------------------------------------------
// wait on a given timer fd and return number of missed wakeups, if any
// TODO: in future, if we have multiple of these, we can use select()
//------------------------------------------------------------------------------
int
timerfd_wait (timerfd_info_t *pinfo, uint64_t *missed)
{
    int         rv;

    // wait for next timer event, and warn any missed events
    *missed = 0;
    rv = read(pinfo->timer_fd, missed, sizeof(*missed));
    if (rv == -1) {
        return -1;
    }
    if (*missed > 1) {
        SDK_TRACE_VERBOSE("Periodic thread missed %" PRIu64 " wakeups", *missed);
    }
    pinfo->missed_wakeups += *missed;
    return 0;
}

}    // namespace lib
}    // namespace sdk
