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


#include <boost/lockfree/queue.hpp>
#include "include/sdk/mem.hpp"
#include "lib/lfq/lfq.hpp"

namespace sdk {
namespace lib {

class lfq::lfq_impl {
public:
    static lfq_impl *factory(uint32_t size=0) {
        void        *mem;
        lfq_impl    *new_lfq_impl;

        mem = SDK_CALLOC(SDK_MEM_ALLOC_LIB_LFQ, sizeof(lfq_impl));
        if (mem == NULL) {
            return NULL;
        }
        if (size) {
            new_lfq_impl = new (mem) lfq_impl(size);
        } else {
            new_lfq_impl = new (mem) lfq_impl();
        }
        if (!new_lfq_impl->queue_.is_lock_free()) {
            new_lfq_impl->~lfq_impl();
            SDK_FREE(SDK_MEM_ALLOC_LIB_LFQ, mem);
            return NULL;
        }
        return new_lfq_impl;
    }

    static void destroy(lfq_impl *q_impl) {
        q_impl->~lfq_impl();
        SDK_FREE(SDK_MEM_ALLOC_LIB_LFQ, q_impl);
    }

    bool enqueue(void *item) { return queue_.push(item); }

    void *dequeue(void) {
        void    *item;
        if (queue_.pop(item)) {
            return item;
        }
        return NULL;
    }

private:
    lfq_impl(uint32_t size):queue_(size) {}
    lfq_impl():queue_() {}
    ~lfq_impl() {}

private:
    boost::lockfree::queue<void *>    queue_;
};

lfq::lfq() {
    lfq_impl_ = NULL;
}

lfq *
lfq::factory(uint32_t size) {
     void        *mem;
     lfq         *new_lfq;
     lfq_impl    *new_lfq_impl;

     mem = SDK_CALLOC(SDK_MEM_ALLOC_LIB_LFQ, sizeof(lfq));
     if (mem == NULL) {
         return NULL;
     }
     new_lfq = new (mem) lfq();

     new_lfq_impl = lfq_impl::factory(size);
     if (new_lfq_impl == NULL) {
         goto end;
     }
    new_lfq->lfq_impl_ = new_lfq_impl;
    return new_lfq;

end:

    if (new_lfq) {
        new_lfq->~lfq();
        SDK_FREE(SDK_MEM_ALLOC_LIB_LFQ, new_lfq);
    }
    return NULL;
}

void
lfq::destroy(lfq *q) {
    lfq_impl::destroy(q->lfq_impl_);
    q->lfq_impl_ = NULL;
    q->~lfq();
    SDK_FREE(SDK_MEM_ALLOC_LIB_LFQ, q);
}

bool
lfq::enqueue(void *item) {
    return lfq_impl_->enqueue(item);
}

void *
lfq::dequeue(void) {
    return lfq_impl_->dequeue();
}

}    // namespace utils
}    // namespace sdk
