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


#ifndef __CRC_FAST_HPP__
#define __CRC_FAST_HPP__

#include "include/sdk/base.hpp"
#include "include/sdk/lock.hpp"

namespace sdk {
namespace utils {

typedef enum crc15_polynomial_type_e {
    CRC15_POLYNOMIAL_TYPE_WAY0      = 0,
    CRC15_POLYNOMIAL_TYPE_WAY1      = 1,
    CRC15_POLYNOMIAL_TYPE_WAY2      = 2,
    CRC15_POLYNOMIAL_TYPE_WAY3      = 3,
    CRC15_POLYNOMIAL_TYPE_MAX,
} crc15_polynomial_type_t;

typedef enum crc16_polynomial_type_e {
    CRC16_POLYNOMIAL_TYPE_WAY0      = 0,
    CRC16_POLYNOMIAL_TYPE_WAY1      = 1,
    CRC16_POLYNOMIAL_TYPE_WAY2      = 2,
    CRC16_POLYNOMIAL_TYPE_WAY3      = 3,
    CRC16_POLYNOMIAL_TYPE_MAX,
} crc16_polynomial_type_t;

typedef enum crc32_polynomial_type_e {
    CRC32_POLYNOMIAL_TYPE_CRC32     = 0,
    CRC32_POLYNOMIAL_TYPE_CRC32C    = 1,
    CRC32_POLYNOMIAL_TYPE_CRC32K    = 2,
    CRC32_POLYNOMIAL_TYPE_CRC32Q    = 3,
    CRC32_POLYNOMIAL_TYPE_MAX,
} crc32_polynomial_type_t;

extern uint16_t crc15(uint8_t const message[], int nBytes, uint8_t poly_index);
extern uint16_t crc16(uint8_t const message[], int nBytes, uint8_t poly_index);
extern uint32_t crc32(uint8_t const message[], int nBytes, uint8_t poly_index);

}   // namespace utils
}   // namespace sdk
#endif    //__CRC_FAST_HPP__
