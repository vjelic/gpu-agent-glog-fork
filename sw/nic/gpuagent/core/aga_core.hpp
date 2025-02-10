
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
/// this file deals with internal API context information
///
//----------------------------------------------------------------------------

#ifndef __AGA_CORE_CORE_HPP__
#define __AGA_CORE_CORE_HPP__

#include "nic/gpuagent/include/globals.hpp"

namespace aga {

enum {
    AGA_THREAD_ID_NONE = aga_thread_id_t::AGA_THREAD_ID_MIN,
    // API thread that handles the configuration operations
    AGA_THREAD_ID_API,
    // event monitoring thread
    AGA_THREAD_ID_EVENT_MONITOR,
    // GPU field watcher thread
    AGA_THREAD_ID_WATCHER,
};

}    // namesapce aga

#endif    // __AGA_CORE_CORE_HPP__
