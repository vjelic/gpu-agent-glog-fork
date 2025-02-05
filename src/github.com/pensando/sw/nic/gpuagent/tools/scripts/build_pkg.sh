#!/bin/bash

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

#set -x
export P4PLUS_VER=${P4PLUS_VER:-16}
export TTOP=${TTOP:-/tmp/build}
SRCDIR=/tmp/build
TOPDIR=/usr/src/github.com/pensando/sw
GEN_SRC_TARBALL="no"
BUILD="no"
P4_PROGRAM='pulsar'
ASIC=salina

print_usage() {
    echo "${0} <--gen-src-tarball [--build] | --build | --clean>"
    echo "  --gen-src-tarball     : generate source tarball"
    echo "  --build               : build binary in the destination folder"
    echo "  --clean               : clean and exit"
    HELP="yes"
}

parse_args() {
    argc=$#
    argv=($@)
    for (( j=0; j<argc; j++ )); do
        if [[ ${argv[j]} =~ '--gen-src-tarball' ]];then
            export GEN_SRC_TARBALL="yes"
            export CLEAN="yes"
        elif [[ ${argv[j]} =~ '--build' ]];then
            BUILD="yes"
        elif [[ ${argv[j]} =~ '--clean' ]];then
            export CLEAN="yes"
        elif [[ ${argv[j]} =~ '-h' ]];then
            print_usage $@
            return 0
        elif [[ ${argv[j]} =~ '--help' ]];then
            print_usage $@
            return 0
        fi
    done
}

finish() {
    echo "Finished!"
}

handle_error() {
    echo "An error occured on line $1"
    exit 1
}

trap finish EXIT
trap 'handle_error $LINENO' ERR

gen_src_tarball() {
    echo "Generating the source tarball"
    cd $SRCDIR
    time tar cf - src | pigz -9 > /sw/gpuagent-src.tar.xz
    echo "Source bundle disk size"
    du -sh $SRCDIR/src /sw/gpuagent-src.tar.xz
    [[ $? -ne 0 ]] && return 1
    echo "Source tarball generated at /sw/gpuagent-src.tar.xz"
}

clean_build_artifacts() {
    echo "Cleaning up build artifacts ..."
    make -C $SRCDIR/src/github.com/pensando/sw/nic/gpuagent/ clean
}

build_src() {
    echo "Building gpuagent inside $SRCDIR"
    make -C $SRCDIR/src/github.com/pensando/sw/nic/gpuagent/ -j 12 SMI=amdsmi
    return $?
}

copy_src() {
    spec=$1
    $TOPDIR/nic/apollo/tools/copy_src.py --src /usr/src/github.com/pensando --dst $SRCDIR/src/github.com/pensando --arch $ARCH --spec $spec $CREATE_LBT --asic $ASIC --pipeline $PIPELINE --platform $PLATFORM
    sync
}

main() {
    parse_args $@
    if [ "$HELP" == "yes" ];then
        return 0
    fi

    mkdir -p $TTOP
    rm -rf $SRCDIR
    mkdir -p $SRCDIR

    if [ $ASIC != "salina" ];then
        echo "$ASIC is not supported for gpuagent package"
        return 1
    fi
    ARCH=x86_64 PIPELINE=rudra PLATFORM=sim copy_src $TOPDIR/nic/gpuagent/tools/scripts/gpuagent_source.spec
    if [ "$CLEAN" == "yes" ]; then
        clean_build_artifacts
    fi
    if [ "$BUILD" == "yes" ]; then
        build_src
        ret_code=$?
        if [[ $ret_code != 0 ]]; then
            echo "Build failed"
            if [ "$GEN_SRC_TARBALL" == "yes" ]; then
                echo "Skipping source tarball generation"
            fi
            return $ret_code
        fi
    fi
    if [ "$GEN_SRC_TARBALL" == "yes" ]; then
        gen_src_tarball
    fi
    return 0
}

main "$@"
