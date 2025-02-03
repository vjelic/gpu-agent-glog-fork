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


#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#include "include/sdk/base.hpp"
#include "ipc_internal.hpp"
#include "subscribers.hpp"

const char *SUBS_SHM_FILE = "/ipc_subs_v2";

using namespace sdk::ipc;
subscribers *subscribers::instance_ = new subscribers();

off_t
subs_size (void)
{
    return sizeof(uint8_t) * (IPC_MAX_CLIENT_ID + 1) *
        (IPC_MAX_BROADCAST_ID + 1);
}

subscribers *
subscribers::instance(void) {
    return subscribers::instance_;
}

subscribers::subscribers() {
    shmopen();
}

subscribers::~subscribers() {
    if (this->subs_) {
        munmap(this->subs_, subs_size());
    }
}

void
subscribers::shmopen(void) {
    int fd;
    struct stat st;
    mode_t old_umask;

    old_umask = umask(0);
    fd = shm_open(ipc_env_suffix(SUBS_SHM_FILE).c_str(),
                  O_RDWR | O_CREAT, 0666);
    if (fd == -1) {
        fprintf(stderr, "open %s failed: %s:%s:%d, %s\n",
            ipc_env_suffix(SUBS_SHM_FILE).c_str(),
            __FILE__, __FUNCTION__, __LINE__,
            strerror(errno));
    }
    assert(fd != -1);
    umask(old_umask);

    // Make sure no two binaries are trying to use the same shared
    // memory with different size of subs. This still leaves the door
    // open for problems where somebody modifies both MAX_ID and
    // MAX_CLIENT but their product is still the same
    fstat(fd, &st);
    assert(st.st_size == 0 || st.st_size == subs_size());

    ftruncate(fd, subs_size());

    this->subs_ = (uint8_t *)mmap(0, subs_size(), PROT_READ | PROT_WRITE,
                                  MAP_SHARED, fd, 0);
    assert(this->subs_ != NULL);
}

void
subscribers::set(uint32_t code, uint32_t client) {
    assert(code <= IPC_MAX_BROADCAST_ID);
    assert(client <= IPC_MAX_CLIENT_ID);
    this->subs_[(code * IPC_MAX_CLIENT_ID) + client] = 1;
}

void
subscribers::clear(uint32_t code, uint32_t client) {
    assert(code <= IPC_MAX_BROADCAST_ID);
    assert(client <= IPC_MAX_CLIENT_ID);
    this->subs_[(code * IPC_MAX_CLIENT_ID) + client] = 0;
}

std::vector<uint32_t>
subscribers::get(uint32_t code) {
    std::vector<uint32_t> subs;
    assert(code <= IPC_MAX_BROADCAST_ID);
    for (int i = 0; i <= IPC_MAX_CLIENT_ID; i++) {
        if (this->subs_[(code * IPC_MAX_CLIENT_ID) + i] == 1) {
            subs.push_back(i);
        }
    }

    return subs;
}
