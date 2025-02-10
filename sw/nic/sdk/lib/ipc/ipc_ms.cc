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


#include "ipc.hpp"
#include "ipc_ms.hpp"

namespace sdk {
namespace ipc {

struct fd_watcher_t {
    handler_cb cb;
    const void *ctx;
};

static void
fd_cb_wrap (int fd, int, void *ctx)
{
    fd_watcher_t *watcher = (fd_watcher_t *)ctx;

    watcher->cb(fd, watcher->ctx);
}

static void *
fd_watch (int fd, handler_cb cb, const void *ipc_ctx, const void *infra_ctx)
{
    fd_watch_ms_cb ms_cb = (fd_watch_ms_cb) infra_ctx;
    fd_watcher_t *watcher = new fd_watcher_t();

    watcher->cb = cb;
    watcher->ctx = ipc_ctx;

    ms_cb(fd, fd_cb_wrap, watcher);
    
    return watcher;
}

static void
fd_unwatch (int fd, void *watcher, const void *infra_ctx)
{
    fd_watcher_t *w = (fd_watcher_t *)watcher;

    // We must call the MS unwatch function here

    delete w;
        
}

void
ipc_init_metaswitch (uint32_t client_id, fd_watch_ms_cb fd_watch_ms_cb)
{

    ipc_init_async(client_id, std::unique_ptr<infra_t>(new infra_t{
                    .fd_watch = fd_watch,
                    .fd_watch_ctx = (void *)fd_watch_ms_cb,
                    .fd_unwatch = fd_unwatch,
                    .fd_unwatch_ctx = NULL,
                    .timer_add = NULL,
                    .timer_add_ctx = NULL,
                    .timer_del = NULL,
                    .timer_del_ctx =  NULL,
                    }), true);
}
        
} // namespace ipc
} // namespace sdk
