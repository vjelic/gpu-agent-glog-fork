#!/usr/bin/python3

#
# Copyright(C) Advanced Micro Devices, Inc. All rights reserved.
#
# You may not use this software and documentation (if any) (collectively,
# the "Materials") except in compliance with the terms and conditions of
# the Software License Agreement included with the Materials or otherwise as
# set forth in writing and signed by you and an authorized signatory of AMD.
# If you do not have a copy of the Software License Agreement, contact your
# AMD representative for a copy.
#
# You agree that you will not reverse engineer or decompile the Materials,
# in whole or in part, except as allowed by applicable law.
#
# THE MATERIALS ARE DISTRIBUTED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR
# REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#


#

#----------------------------------------------------------------------------
#
# \file
# event subscribe gRPC client testapp
#
#----------------------------------------------------------------------------

import time
import json
import threading
import argparse
import uuid
import logging
import grpc

import events_pb2
import events_pb2_grpc

logger = None

# read and parse user arguments
parser = argparse.ArgumentParser()
parser.add_argument("--node-ip", help="compute node ip address", required=True)
parser.add_argument("--grpc-port", help="gpuagent gRPC port (default=50061)", default="50061", type=str)
parser.add_argument("--id", help="comma separated gpu uuid list", type=str, required=True)
parser.add_argument("--events", help="comma separated events list (numbers only)", type=str, required=True)
args = parser.parse_args()
node_ip = args.node_ip
grpc_port = args.grpc_port
events_str = args.events
uuid_str = args.id

def setup_logging():
    global logger
    console = logging.StreamHandler()
    console.setLevel(logging.INFO)
    logging.getLogger('').addHandler(console)
    logging.root.setLevel(logging.INFO)
    logger = logging.getLogger(__name__)

def events_subscribe_request():
    grpcmsg = events_pb2.EventSubscribeRequest()
    ids = events_str.split(",")
    for id in ids:
        grpcmsg.Filter.Events.Id.append(int(id))
    ids = uuid_str.split(",")
    for id in ids:
        grpcmsg.Filter.Gpu.append(uuid.UUID(id).bytes)
    return grpcmsg

def events_subscribe(node_ip, grpc_port):
    channel = grpc.insecure_channel(node_ip + ':' + grpc_port)
    stub = events_pb2_grpc.EventSvcStub(channel)
    resp = stub.EventSubscribe(events_subscribe_request())
    while True:
        response = next(resp)
        logger.info(f"{response}")
    logger.info("Events subscription completed\n")

def spawn_events_threads():
    t = threading.Thread(target=events_subscribe, args=(node_ip, grpc_port,))
    t.daemon = True
    t.start()
    t.join()

def Main():
    setup_logging()
    spawn_events_threads()

Main()
