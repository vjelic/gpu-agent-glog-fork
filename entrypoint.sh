#!/bin/sh

dir=/usr/src/github.com/ROCm/gpu-agent/sw
outdir=/usr/src/github.com/ROCm/gpu-agent/sw/nic/build/
grpcdir=$dir/nic/third-party/grpc
protodir=$dir/nic/third-party/protobuf
zeromqdir=$dir/nic/third-party/libzmq
libevdir=$dir/nic/third-party/libev-4.33
boostdir=$dir/nic/third-party/boost_1_88_0
abesildir=$dir/nic/third-party/abseil-cpp

# Build protobuf
cd $protodir &&\
./autogen.sh && \
./configure --prefix=$outdir && \
make -j$(nproc) && \
make install && \
ldconfig


# build abseil-cpp
cd $abesildir && \
mkdir -p cmake/build && \
cd cmake/build && \
cmake -DCMAKE_INSTALL_PREFIX=$outdir \
  ../../ && \
make -j$(nproc) && \
make install && \
ldconfig

# Build grpc and grpc_cpp_plugin
cd $grpcdir && \
mkdir -p $grpcdir/cmake/build && \
cd $grpcdir/cmake/build && \
cmake -DgRPC_INSTALL=ON \
  -DgRPC_BUILD_TESTS=OFF \
  -DCMAKE_INSTALL_PREFIX=$outdir \
  ../../ && \
make -j$(nproc) && \
make install && \
ldconfig

cp $grpcdir/cmake/build/grpc_cpp_plugin /usr/local/bin/grpc_cpp_plugin

dnf install -y --nobest gcc-c++

#Build and install ZeroMQ from source
cd $zeromqdir && \
./autogen.sh && \
./configure --prefix=$outdir && \
make -j$(nproc) && \
make install && \
ldconfig

#build libev from source
cd $libevdir && \
./configure --prefix=$outdir && \
make -j$(nproc) && \
make install && \
ldconfig

#build boost from source
cd $boostdir && \
./bootstrap.sh --prefix=$outdir && \
./b2 install

# remove share folder (this has a main inside it on boost lib builder)
rm -rf $outdir/share

cd $dir/nic
make -C gpuagent

# drop to the builder shell with libraries built
/bin/bash
