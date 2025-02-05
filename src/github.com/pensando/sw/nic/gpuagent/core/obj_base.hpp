
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
/// base object definition for all objects in the agent
///
//----------------------------------------------------------------------------

#ifndef __AGA_CORE_OBJ_BASE_HPP__
#define __AGA_CORE_OBJ_BASE_HPP__

namespace aga {

/// \brief base class for all objects
class obj_base {
public:
    /// \brief constructor
    obj_base(){};

    /// \brief destructor
    virtual ~obj_base() {};
};

}    // namespace aga

using aga::obj_base;

#endif    // __AGA_CORE_OBJ_BASE_HPP__
