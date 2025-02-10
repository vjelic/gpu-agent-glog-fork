
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
/// front-end agent for rdcd
///
//----------------------------------------------------------------------------

#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <inttypes.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <grpc++/grpc++.h>
#include "nic/sdk/include/sdk/base.hpp"
#include "nic/sdk/include/sdk/assert.hpp"
#include "nic/gpuagent/include/globals.hpp"
#include "nic/gpuagent/init.hpp"
#include "nic/gpuagent/svc/gpu.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

/// \brief    print usage information
static void inline
print_usage (char **argv)
{
    fprintf(stdout, "Usage : %s [-p <port> | --grpc-server-port <port>]\n\n",
            argv[0]);
    fprintf(stdout, "Use -h | --help for help\n");
}

int
main (int argc, char **argv)
{
    int oc;
    sdk_ret_t ret;
    aga_init_params_t init_params = {};
    // command line options
    struct option longopts[] = {
        { "grpc-server-port", required_argument, NULL, 'p' },
        { "rdc-server",       required_argument, NULL, 's' },
        { "help",             no_argument,       NULL, 'h' },
        { 0,                  0,                 NULL,  0  }
    };

    // parse CLI options
    while ((oc = getopt_long(argc, argv, ":hp:s:W;", longopts, NULL)) != -1) {
        switch (oc) {
        case 'p':
            try {
                int port = std::stoi(optarg);
                if ((port <= 0) || (port > 65535)) {
                    fprintf(stderr, "Invalid gRPC server port %d specified\n",
                            port);
                    print_usage(argv);
                    exit(1);
                }
            } catch (const std::invalid_argument &e) {
                fprintf(stderr, "Invalid gRPC server port specified\n");
                print_usage(argv);
                exit(1);
            }
            init_params.grpc_server = std::string("0.0.0.0:") + optarg;
            break;

        case 's':
            init_params.rdc_server = optarg;
            if (init_params.rdc_server.empty()) {
                fprintf(stderr, "rdcd server IP is not specified\n");
                print_usage(argv);
                exit(1);
            }
            init_params.rdc_server +=
                ":" + std::to_string(AGA_DEFAULT_RDC_GRPC_SERVER_PORT);
            break;

        case 'h':
            print_usage(argv);
            exit(0);
            break;

        default:
            // ignore all other options
            break;
        }
    }
    // use default IP for rdc server if not specified
    if (init_params.rdc_server.empty()) {
        init_params.rdc_server =
            "127.0.0.1:" + std::to_string(AGA_DEFAULT_RDC_GRPC_SERVER_PORT);
    }
    // use default IP, port for gRPC server if not specified
    if (init_params.grpc_server.empty()) {
        init_params.grpc_server =
            "0.0.0.0:" + std::to_string(AGA_DEFAULT_GRPC_SERVER_PORT);
    }
    // initialize the agent
    ret = aga_init(&init_params);
    SDK_ASSERT(ret == SDK_RET_OK);
    fprintf(stderr, "gRPC server exited, agent shutting down ...\n");
    return 0;
}
