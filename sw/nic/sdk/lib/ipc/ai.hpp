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


#ifndef __PENIPC_AI_HPP__
#define __PENIPC_AI_HPP__

#include <memory>

#include "ipc.hpp"

#define AI_MSG_SIZE     4096

namespace sdk {
namespace ipc {

class ai_client {
 public:
     static std::shared_ptr<ai_client> create(uint32_t card_id);
     virtual ipc_msg_ptr request(uint32_t endpoint, uint32_t opcode,
             void *data, size_t length) = 0;

};
using ai_client_ptr = std::shared_ptr<ai_client>;

} // namespace ipc
} // namespace sdk

#endif
