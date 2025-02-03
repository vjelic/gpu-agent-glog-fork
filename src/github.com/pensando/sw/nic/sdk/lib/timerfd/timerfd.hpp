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


//------------------------------------------------------------------------------

//
// timerfd library is a wrapper around linux timerfd APIs
//------------------------------------------------------------------------------

#ifndef __SDK_TIMERFD_HPP__
#define __SDK_TIMERFD_HPP__

#include <sdk/base.hpp>

namespace sdk {
namespace lib {

typedef struct timerfd_info_s {
    int         timer_fd;
    uint64_t    usecs;
    uint64_t    missed_wakeups;
} timerfd_info_t;

void timerfd_init(timerfd_info_t *timerfd_info);
int timerfd_prepare(timerfd_info_t *timerfd_info);
int timerfd_wait(timerfd_info_t *timerfd_info, uint64_t *missed);

}    // namespace lib
}    // namespace sdk

using sdk::lib::timerfd_info_t;

#endif    // __SDK_TIMERFD_HPP__

