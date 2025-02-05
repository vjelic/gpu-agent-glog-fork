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
///
/// \file
/// debug node for gpuctl command line interface
///
//------------------------------------------------------------------------------

package cmd

import (
	"github.com/spf13/cobra"
)

func RegisterDebugNodes(cmd *cobra.Command) {}

// debugCmd represents the debug command
var debugCmd = &cobra.Command{
	Use:   "debug",
	Short: "debug commands",
	Long:  "debug commands",
}

var DebugCreateCmd = &cobra.Command{
	Use:   "create",
	Short: "debug create commands",
	Long:  "debug create commands",
}

var DebugUpdateCmd = &cobra.Command{
	Use:   "update",
	Short: "debug update commands",
	Long:  "debug update commands",
}

var DebugDeleteCmd = &cobra.Command{
	Use:   "delete",
	Short: "debug delete commands",
	Long:  "debug delete commands",
}

func init() {
	RootCmd.AddCommand(debugCmd)
	RegisterDebugNodes(debugCmd)

	debugCmd.AddCommand(DebugCreateCmd)
	debugCmd.AddCommand(DebugUpdateCmd)
	debugCmd.AddCommand(DebugDeleteCmd)
}
