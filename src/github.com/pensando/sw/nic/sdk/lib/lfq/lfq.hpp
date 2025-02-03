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
// lock free multi-producer, multi-consumer queue
//------------------------------------------------------------------------------

#ifndef __LFQ_HPP__
#define __LFQ_HPP__

#include "include/sdk/base.hpp"

namespace sdk {
namespace lib {

class lfq {
public:
    static lfq *factory(uint32_t size=0);
    static void destroy(lfq *q);
    bool enqueue(void *item);
    void *dequeue(void);

private:
    // forward declaration
    class lfq_impl;
    lfq_impl *lfq_impl_;

private:
    lfq();
    ~lfq() {}
};

}    // namespace utils
}    // namespace sdk

#endif    // __LFQ_HPP__

