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


#ifndef __SDK_IPC_SUBSCRIBERS_H__
#define __SDK_IPC_SUBSCRIBERS_H__

#include <vector>

#include <stdint.h>

#include "ipc.hpp"

namespace sdk {
namespace ipc {

class subscribers {
public:
    void set(uint32_t code, uint32_t client);
    void clear(uint32_t code, uint32_t client);
    std::vector<uint32_t> get(uint32_t code);
    static subscribers *instance(void);
private:
    static subscribers *instance_;
    subscribers();
    ~subscribers();
    void shmopen(void);
    uint8_t *subs_;
};

} // namespace sdk
} // namespace ipc

#endif // __SDK_IPC_SUBSCRIBERS_H__
