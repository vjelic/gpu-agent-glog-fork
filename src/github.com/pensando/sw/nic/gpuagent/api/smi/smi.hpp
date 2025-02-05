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
//----------------------------------------------------------------------------
///
/// \file
/// common smi header file
///
//----------------------------------------------------------------------------

#ifndef __AGA_API_SMI_HPP__
#define __AGA_API_SMI_HPP__

#include "nic/sdk/include/sdk/base.hpp"
#ifndef ROCM_SMI
#include "nic/third-party/rocm/amd_smi_lib/include/amd_smi/amdsmi.h"

typedef amdsmi_processor_handle aga_gpu_handle_t;
#else
typedef uint32_t aga_gpu_handle_t;
#endif

#endif    // __AGA_API_SMI_HPP__
