GPU Agent provides programmable APIs to configure and monitor AMD Instinct GPUs

To build GPU Agent, follow the steps below:

1. setup workspace (required once)

```
# make setup-ws
```

2. create build container image (required once)

```
# make build-container
```
   

3. building gpuagent binary
```
# make gpuagent
```


4. artifacts location
  - gpuagent binary can be found at - ${TOP_DIR}/sw/nic/build/x86_64/sim/bin/gpuagent

5. To clean the build artifacts (run it within build-container)

```
# make gpuagent-shell
[root@builder-container sw]# make -C nic/gpuagent clean
[root@builder-container sw]# exit
exit

```
