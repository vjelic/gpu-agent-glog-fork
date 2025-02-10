To build gpuagent, follow the steps below:

```
1. use the Dockerfile-u22.04 file to build docker image like below:

   docker build . -f Dockerfile-u22.04 -t u22.04-gpuagent

2. once docker image is built, launch the docker with the following command:

   docker run -ti u22.04-gpuagent bash

3. inside the docker:
   mkdir -p /home/amd/
   cd /home/amd/
   git clone <gpuagent-repo-URL>
   cd gpu-agent/src/github.com/pensando/sw/nic
   make -C gpuagent

4. gpuagent binary can be found at - /home/amd/src/github.com/pensando/sw/nic/build/x86_64/sim/bin/gpuagent
```

To clean the build artifacts:

```
1. cd /home/amd/src/github.com/pensando/sw/nic
2. make -C gpuagent clean
```
