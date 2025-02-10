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
// SDK lock primitives
//------------------------------------------------------------------------------

#ifndef __SDK_LOCK_HPP__
#define __SDK_LOCK_HPP__

#if !defined(RTOS) || defined(CONFIG_BOARD_SIM)
#include <pthread.h>
#else
#include <zephyr/posix/pthread.h>
#endif
#include "include/sdk/base.hpp"

typedef pthread_spinlock_t    sdk_spinlock_t;

#define SDK_SPINLOCK_INIT(slock, mtype)       pthread_spin_init((slock), mtype)
#define SDK_SPINLOCK_DESTROY(slock)           pthread_spin_destroy((slock))
#define SDK_SPINLOCK_LOCK(slock)              pthread_spin_lock((slock))
#define SDK_SPINLOCK_UNLOCK(slock)            pthread_spin_unlock((slock))

static inline int
sdk_spinlock_trylock (sdk_spinlock_t *lock)
{
    return pthread_spin_trylock(lock);
}

#if defined(__cplusplus) && !defined(RTOS)
namespace sdk {
//------------------------------------------------------------------------------
// writer preferred read-write lock implemented using spinlocks ... this lock is
// safe for use by real-time (FTE threads) and control threads (like cfg
// thread). if there is a writer waiting (on active readers) for the lock, no
// new reader coming after the writer will acquire the lock, this avoids
// starving of the writer forever
//------------------------------------------------------------------------------
class wp_rwlock {
public:
    wp_rwlock() {
        SDK_SPINLOCK_INIT(&mutex_, PTHREAD_PROCESS_SHARED);
        nwriters_ = nreaders_ = 0;
    }

    ~wp_rwlock() { SDK_SPINLOCK_DESTROY(&mutex_); }

    void rlock(void) {
        uint32_t wcount;

        do {
            SDK_SPINLOCK_LOCK(&mutex_);
            SDK_ATOMIC_LOAD_UINT32(&nwriters_, &wcount);
            if (wcount) {
                SDK_SPINLOCK_UNLOCK(&mutex_);
            } else {
                break;
            }
        } while (true);
        SDK_ATOMIC_INC_UINT32(&nreaders_, 1);
        SDK_SPINLOCK_UNLOCK(&mutex_);
    }

    void runlock(void) {
        SDK_SPINLOCK_LOCK(&mutex_);
        SDK_ATOMIC_DEC_UINT32(&nreaders_, 1);
        SDK_SPINLOCK_UNLOCK(&mutex_);
    }

    void wlock(void) {
        uint32_t rcount;

        SDK_ATOMIC_INC_UINT32(&nwriters_, 1);
        do {
            SDK_SPINLOCK_LOCK(&mutex_);
            SDK_ATOMIC_LOAD_UINT32(&nreaders_, &rcount);
            if (rcount) {
                SDK_SPINLOCK_UNLOCK(&mutex_);
            } else {
                break;
            }
        } while (true);
    }

    void wunlock(void) {
        SDK_ATOMIC_DEC_UINT32(&nwriters_, 1);
        SDK_SPINLOCK_UNLOCK(&mutex_);
    }

private:
    sdk_spinlock_t    mutex_;    // used for mutual exclusion between writers, readers
    uint32_t          nwriters_; // no. of writers that are active or waiting
    uint32_t          nreaders_; // no. of active readers
};
}    // namespace sdk
#endif    // __cplusplus && !RTOS

#endif    // __SDK_LOCK_HPP__
