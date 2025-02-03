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
/// smi layer APIs
///
//----------------------------------------------------------------------------

#ifndef __AGA_API_SMI_API_HPP__
#define __AGA_API_SMI_API_HPP__

#include "nic/sdk/include/sdk/base.hpp"
#include "nic/gpuagent/api/include/aga_init.hpp"
#include "nic/gpuagent/api/include/aga_gpu.hpp"
#include "nic/gpuagent/api/include/aga_task.hpp"
#ifndef ROCM_SMI
#include "nic/third-party/rocm/amd_smi_lib/include/amd_smi/amdsmi.h"

typedef amdsmi_processor_handle aga_gpu_handle_t;
#else
typedef uint32_t aga_gpu_handle_t;
#endif

namespace aga {

/// \defgroup AGA_SMI - smi module APIs
/// \ingroup AGA
/// @{

/// \brief    initialize smi layer
/// \param[in] init_params    initialization parameters
/// \return     SDK_RET_OK or error code in case of failure
sdk_ret_t smi_init(aga_api_init_params_t *init_params);

/// \brief    fill gpu object config specification
/// \param[in] handle    GPU handle
/// \param[out] spec    operational status to be filled
/// \return     SDK_RET_OK or error code in case of failure
sdk_ret_t smi_gpu_fill_spec(aga_gpu_handle_t handle,
                            aga_gpu_spec_t *spec);

/// \brief    fill gpu object operational status
/// \param[in] handle    GPU handle
/// \param[out] status    operational status to be filled
/// \return     SDK_RET_OK or error code in case of failure
sdk_ret_t smi_gpu_fill_status(aga_gpu_handle_t handle, uint32_t id,
                              aga_gpu_status_t *status);

/// \brief    fill gpu object statistics
/// \param[in] handle    GPU handle
/// \param[out] stats    gpu object stats to be filled
/// \return     SDK_RET_OK or error code in case of failure
sdk_ret_t smi_gpu_fill_stats(aga_gpu_handle_t handle,
                             aga_gpu_stats_t *stats);

/// \brief    read all the events and invokve the callback provided for each
/// \param[in] cb    callback function pointer
/// \param[in] ctxt  opaque context passed back to the callback
/// \return     SDK_RET_OK or error code in case of failure
sdk_ret_t smi_event_read_all(aga_event_read_cb_t cb, void *ctxt);

/// \brief     reset gpu or a specific gpu setting
/// \param[in] handle    GPU handle
/// \param[in] reset_type    type of the reset
/// \return    SDK_RET_OK or error code in case of failure
sdk_ret_t smi_gpu_reset(aga_gpu_handle_t handle,
                        aga_gpu_reset_type_t reset_type);

/// \brief     update gpu object
/// \param[in] handle       GPU handle
/// \param[in] spec     spec with updated attributes
/// \param[in] upd_mask updated attributes bitmask
/// \return    SDK_RET_OK or error code in case of failure
sdk_ret_t smi_gpu_update(aga_gpu_handle_t handle, aga_gpu_spec_t *spec,
                         uint64_t upd_mask);

/// \brief     fill gpu device topology
/// \param[in] gpu_handle   GPU handle
/// \param[out] info    GPU topology information
/// \return    SDK_RET_OK or error code in case of failure
sdk_ret_t smi_gpu_fill_device_topology(aga_gpu_handle_t handle,
                                       aga_device_topology_info_t *info);

/// \brief     discover gpu devices
/// \param[out] num_gpus    number of GPU devices discovered
/// \param[out] gpu_handles handle of gpu devices discovered
/// \param[out] gpu_keys    uuids of gpu devices discovered
/// \return    SDK_RET_OK or error code in case of failure
sdk_ret_t smi_discover_gpus(uint32_t *num_gpus,
                            aga_gpu_handle_t *gpu_handles,
                            aga_obj_key_t *gpu_keys);

/// \brief function to get number of bad pages for GPU
/// \param[in]  gpu             GPU object
/// \param[out] num_bad_pages   number of bad pages
/// \return SDK_RET_OK or error code in case of failure
sdk_ret_t smi_gpu_get_bad_page_count(void *gpu_obj,
                                     uint32_t *num_bad_pages);

/// \brief function to get GPU bad page records
/// \param[in]  gpu           GPU object
/// \param[in]  num_bad_pages number of bad pages
/// \param[out] records       GPU bad page records
/// \return SDK_RET_OK or error code in case of failure
sdk_ret_t smi_gpu_get_bad_page_records(void *gpu_obj,
                                       uint32_t num_bad_pages,
                                       aga_gpu_bad_page_record_t *records);

/// \brief function to get GPU partition id
/// \param[in]  gpu_handle   handle of GPU device
/// \param[out] partition_id partition id of the GPU
sdk_ret_t smi_get_gpu_partition_id(aga_gpu_handle_t gpu_handle,
                                   uint32_t *partition_id);

/// \@}

}    // namespace aga

#endif    // __AGA_API_SMI_API_HPP__
