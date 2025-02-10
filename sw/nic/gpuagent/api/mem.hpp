
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
/// this file captures memory related helpers
///
//----------------------------------------------------------------------------

#ifndef __AGA_API_MEM_HPP__
#define __AGA_API_MEM_HPP__

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/sdk/include/sdk/timestamp.hpp"

#define AGA_DELAY_DELETE_SECS       2

namespace aga {

/// \brief wrapper function to delay delete elements
///
/// \param[in] obj_id       object identifier
/// \param[in] elem         element to free
/// \param[in] timeout_secs optional timeout in seconds to delay delete the
///                         element
/// \return #SDK_RET_OK on success, failure status code on error
///
/// \remark
///   - currently delay delete timeout is AGA_DELAY_DELETE_MSECS, it is
///     expected that other thread(s) using (a pointer to) this object should
///     be done using this object within this timeout or else this memory can
///     be freed and allocated for other objects and can result in corruptions.
///     essentially, AGA_DELAY_DELETE is assumed to be infinite
sdk_ret_t delay_delete(uint32_t obj_id, void *elem,
                       uint64_t timeout_secs = AGA_DELAY_DELETE_SECS);

}    // namespace aga

#endif    // __AGA_CORE_MEM_HPP__
