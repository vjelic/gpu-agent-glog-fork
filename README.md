GPU Agent provides programmable APIs to configure and monitor AMD Instinct GPUs

To build GPU Agent, follow the steps below:

1. setup workspace (required once)

```
# git submodule update --init  --recursive -f
```

2. create build container image (required once)

```
# make build-container
```

3. vendor setup workspace (required once)
  - choose build/developer environment
    - rhel9 
      ```bash
      $ GPUAGENT_BLD_CONTAINER_IMAGE=gpuagent-builder-rhel:9 make docker-shell
      ```

    - ubuntu 22.04
      ```bash
       $ GPUAGENT_BLD_CONTAINER_IMAGE=gpuagent-bldr-ubuntu:22.04 make docker-shell
      ```

  - golang vendor setup
  ```bash
  [root@dev gpu-agent]# cd sw/nic/gpuagent/
  [root@dev gpuagent]# go mod vendor

  ```

4. building artifacts
  - choose build base os
    - rhel9
      ```bash
      # GPUAGENT_BLD_CONTAINER_IMAGE=gpuagent-builder-rhel:9 make gpuagent
      ```

    - ubuntu 22.04
      ```bash
      $ GPUAGENT_BLD_CONTAINER_IMAGE=gpuagent-bldr-ubuntu:22.04 make docker-shell
      ```

5. artifacts location
  - gpuagent binary can be found at - ${TOP_DIR}/sw/nic/build/x86_64/sim/bin/gpuagent
  - gpuctl binary can be found at - ${TOP_DIR}/sw/nic/build/x86_64/sim/bin/gpuctl

6. To clean the build artifacts (run it within build-container)

```bash
[root@dev gpu-agent]# make -C sw/nic/gpuagent clean
[root@dev gpu-agent]# 
```

