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

package utils

import (
	"bytes"
	"fmt"
	"strings"

	uuid "github.com/satori/go.uuid"
)

func IsUUIDValid(u string) error {
	_, err := uuid.FromString(u)
	if err != nil {
		return fmt.Errorf("Incorrect id %v", u)
	}
	return nil
}

func IdToStr(id []byte) string {
	str := "-"
	if id != nil {
		if !bytes.Equal(id, make([]byte, len(id))) {
			str = uuid.FromBytesOrNil(id).String()
		}
	}
	return str
}

// EnableDisableToBool convert strings enable/disable to bool true/false
// returns error if string is invalid
func EnableDisableToBool(str string) (bool, error) {
	switch strings.ToLower(str) {
	case "enable":
		return true, nil
	case "disable":
		return false, nil
	default:
		return false, fmt.Errorf("Unexpected string")
	}
}
