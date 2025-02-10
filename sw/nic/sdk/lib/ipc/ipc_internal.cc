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


#include <string>
#include <stdlib.h>

#include "ipc_internal.hpp"

#define IPC_SUFFIX_ENV "IPC_SUFFIX"

const std::string
ipc_env_suffix (std::string original)
{
    const char *suffix;
    
    suffix = getenv(IPC_SUFFIX_ENV);
    if (suffix == NULL) {
        return std::string(original);
    }

    return std::string(original) + std::string(suffix);
}

