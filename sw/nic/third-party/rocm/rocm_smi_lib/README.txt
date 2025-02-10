instuctions to compile rocm_smi library

1. clone rocm_smi_lib from sw repo:
===================================
a. cd <workspace>/sw/nic
b. git clone  https://github.com/ROCm/rocm_smi_lib
c. cd rocm_smi_lib/
d. git fetch origin
e. git checkout <tag>

2. go to docker shell
==================
a. make docker/shell

3. install dependencies in docker/shell:
=====================================
a. sudo yum search devtool | grep 11 | grep toolchain
   Note: above step is only to search for the toolchain, can be skipped
b. sudo yum install -y devtoolset-11-toolchain.x86_64
c. sudo yum install cmake3

4. compile rocm_smi lib:
=====================
a. cd rocm_smi_lib/
b. mkdir build
c. cd build/
d. CC=/opt/rh/devtoolset-11/root/usr/bin/cc CXX=/opt/rh/devtoolset-11/root/usr/bin/c++ cmake3 ..
e. make -j10

after step 5 above, libs will generated under rocm_smi/
