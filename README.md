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

```
# $ make gpuagent-shell
[root@dev sw]# cd nic/gpuagent/
[root@dev gpuagent]# go mod vendor

```

4. building artifacts
```
# make gpuagent
```

5. artifacts location
  - gpuagent binary can be found at - ${TOP_DIR}/sw/nic/build/x86_64/sim/bin/gpuagent
  - gpuctl binary can be found at - ${TOP_DIR}/sw/nic/build/x86_64/sim/bin/gpuctl

6. To clean the build artifacts (run it within build-container)

```
[root@builder-container sw]# make -C nic/gpuagent clean
[root@builder-container sw]# exit
```

