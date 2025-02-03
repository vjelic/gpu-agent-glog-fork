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


#ifndef __SDK_IPC_MS_HPP__
#define __SDK_IPC_MS_HPP__

#include <stdint.h>

#include "ipc.hpp"

namespace sdk {
namespace ipc {

typedef void (*handler_ms_cb)(int fd, int, void *ctx);

typedef void (*fd_watch_ms_cb)(int fd, handler_ms_cb cb, void *cb_ctx);

extern void ipc_init_metaswitch(uint32_t client_id,
                                fd_watch_ms_cb fw_watch_ms_cb);

}
}

#endif
