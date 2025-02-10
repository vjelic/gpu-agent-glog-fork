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
// logger library for SDK
//------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include "logger.h"

#define SDK_LOGGER_MODULE_ID_INVALID    -1
static __thread int t_mod_id = SDK_LOGGER_MODULE_ID_INVALID;
static int g_main_mod_id = SDK_LOGGER_MODULE_ID_INVALID;

#if defined(RTOS)
static __thread logger_trace_cb_t trace_cb_ = NULL;
#else
logger_trace_cb_t trace_cb_ = NULL;
#endif

void
logger_init (logger_trace_cb_t trace_cb)
{
    trace_cb_ = trace_cb;
}

int
null_logger_cb_ (uint32_t mod_id, trace_level_e trace_level,
                 const char *fmt, ...)
{
    return 0;
}

int
stdout_logger_cb_ (uint32_t mod_id, trace_level_e trace_level,
                   const char *fmt, ...)
{
    char logbuf[1024];
    va_list args;

    va_start(args, fmt);
    vsnprintf(logbuf, sizeof(logbuf), fmt, args);
    return printf("%s\n", logbuf);
}

logger_trace_cb_t
logger_trace_cb (void)
{
    return trace_cb_ ? trace_cb_ : stdout_logger_cb_;
}

// register module_id of a module(thread)
// note: register only for those module which
//       run in a separate thread context.
void
logger_register_module_id (int module_id)
{
    t_mod_id = module_id;
    // module-id first module(thread) to register in a process is the
    // main module id, and is the default id used for SDK logging
    if (g_main_mod_id == -1) {
        g_main_mod_id = t_mod_id;
    }
}

int
logger_get_module_id (void)
{
    int module_id;

    if (t_mod_id < 0) {
        if (g_main_mod_id < 0) {
            module_id =  SDK_LOGGER_MODULE_ID_INVALID;
        } else {
            module_id = g_main_mod_id;
        }
    } else {
        module_id = t_mod_id;
    }
    return module_id;
}

bool
logger_is_trace_cb_set (void)
{
    return ((trace_cb_) ? true : false);
}
