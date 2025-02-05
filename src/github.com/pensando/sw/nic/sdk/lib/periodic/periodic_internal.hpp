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
/// internal header file for periodic thread
///
//----------------------------------------------------------------------------

#ifndef __PERIODIC_INTERNAL_HPP__
#define __PERIODIC_INTERNAL_HPP__

#include "include/sdk/base.hpp"
#include "lib/twheel/twheel.hpp"

namespace sdk {
namespace lib {

// global timer wheel for periodic thread's use
extern sdk::lib::twheel *g_twheel;
// g_twheel_is_running is set to true when timer wheel starts
extern volatile bool g_twheel_is_running;
// g_periodic_thread_ready is set to true when thread starts running
extern volatile bool g_periodic_thread_ready;

}    // namespace lib
}    // namespace sdk

#endif    // __PERIODIC_INTERNAL_HPP__

