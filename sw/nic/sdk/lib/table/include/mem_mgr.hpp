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
// memory manager definition for sdk tables
//------------------------------------------------------------------------------
#ifndef __SDK_TABLE_MEM_MGR_HPP__
#define __SDK_TABLE_MEM_MGR_HPP__

using namespace std;

namespace sdk {
namespace table {

typedef void * (*mem_mgr_alloc_cb_t)(uint32_t mem_alloc_id, const size_t size,
                                     const void *ctx);
typedef void (*mem_mgr_free_cb_t)(uint32_t mem_alloc_id, void *mem);

/// class used to specify custom alloc and free functions to be
/// used by slhash and sltcam libraries
class mem_mgr {
public:
    sdk_ret_t init(mem_mgr_alloc_cb_t alloc_cb, void *alloc_ctx,
                   mem_mgr_free_cb_t free_cb) {
        free_cb_ = free_cb;
        alloc_cb_ = alloc_cb;
        alloc_ctx_ = alloc_ctx;
        return SDK_RET_OK;
    }
    static mem_mgr *factory(mem_mgr_alloc_cb_t alloc_cb, void *alloc_ctx,
                            mem_mgr_free_cb_t free_cb) {
        sdk_ret_t ret;
        void      *mem;
        mem_mgr   *new_mem_mgr;

        // both alloc and free cbs need to be specified
        if ((alloc_cb == NULL) || (free_cb == NULL)) {
            return NULL;
        }

        mem = SDK_CALLOC(SDK_MEM_ALLOC_LIB_TABLE, sizeof(mem_mgr));
        if (!mem) {
            return NULL;
        }

        new_mem_mgr = new (mem) mem_mgr();
        ret = new_mem_mgr->init(alloc_cb, alloc_ctx, free_cb);
        if (ret != SDK_RET_OK) {
            new_mem_mgr->~mem_mgr();
            SDK_FREE(SDK_MEM_ALLOC_LIB_TABLE, new_mem_mgr);
            return NULL;
        }
        return new_mem_mgr;
    }
    void *alloc(uint32_t mem_alloc_id, const std::size_t size) {
        if (alloc_cb_) {
            return alloc_cb_(mem_alloc_id, size, alloc_ctx_);
        } else {
            return NULL;
        }
    }
    void free(uint32_t mem_alloc_id, void *mem) {
        if (free_cb_) {
            return free_cb_(mem_alloc_id, mem);
        }
    }

private:
    mem_mgr_free_cb_t  free_cb_;
    mem_mgr_alloc_cb_t alloc_cb_;
    void               *alloc_ctx_;
};

} // namespace table
} // namespace sdk
#endif // __SDK_TABLE_MEM_MGR_HPP__
