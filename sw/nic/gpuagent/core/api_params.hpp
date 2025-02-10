
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
/// this file contains API params definition
///
//----------------------------------------------------------------------------

#ifndef __AGA_CORE_API_PARAMS_HPP__
#define __AGA_CORE_API_PARAMS_HPP__

#include "nic/gpuagent/core/api.h"
#include "nic/gpuagent/core/obj.h"
#include "nic/gpuagent/api/include/base.hpp"

namespace aga {

/// \brief    this class is used by core framework to stash all the  API
///           specific attributes while the object is being operated on
class api_params_base {
public:
    /// \brief    allocate an instance of this class
    static api_params_base *factory(void);

    /// \brief    destroy and free given instance of this class
    /// param[in] obj_id        object id/type
    /// param[in] api_op        API operation being performed
    /// param[in] api_params    api params instance to be freed
    static void destroy(obj_id_t obj_id, api_op_t api_op,
                        api_params_base *api_params);

    /// \brief    return reference to the object key
    /// param[in] obj_id    object id/type
    /// param[in] api_op    API operation being performed
    /// \return reference to the object's key
    virtual const aga_obj_key_t& obj_key(obj_id_t obj_id,
                                         api_op_t api_op) {
        static const aga_obj_key_t aga_obj_key_invalid = { 0 };

        return aga_obj_key_invalid;
    }
protected:
    /// \brief constructor
    api_params_base() {}

    /// \brief destructor
    virtual ~api_params_base() {}
};

}    // namespace aga

using aga::api_params_base;

#endif    // __AGA_CORE_API_PARAMS_HPP__
