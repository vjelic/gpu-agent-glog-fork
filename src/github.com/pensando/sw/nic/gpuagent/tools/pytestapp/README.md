Instructions for running pytest app inside workspace
====================================================
```
cd <WORKSPACE>/sw/nic
export PYTHONPATH=build/x86_64/sim/rudra/elba/gen/proto/gpuagent/:build/x86_64/sim/rudra/elba/gen/proto
python3 gpuagent/tools/pytestapp/apps/<pytestapp> [arguments]
e.g: python3 gpuagent/tools/pytestapp/apps/gpu_watch_client.py --node-ip 10.30.62.222 --id 31000000-0000-0000-0000-000000000000
```

Instructions for running pytest app outside workspace
=====================================================
From your workspace (one time operation)
```
export PYTESTAPPROOT=/home/$USER/pytest
mkdir -p ${PYTESTAPPROOT}
mkdir -p ${PYTESTAPPROOT}/proto
mkdir -p ${PYTESTAPPROOT}/proto/gpuagent

cd <WORKSPACE>/sw/nic
cp build/x86_64/sim/rudra/elba/gen/proto/gpuagent/* ${PYTESTAPPROOT}/proto/gpuagent
cp build/x86_64/sim/rudra/elba/gen/proto/* ${PYTESTAPPROOT}/proto/
cp gpuagent/tools/pytestapp/apps/* ${PYTESTAPPROOT}/apps/

cd ${PYTESTAPPROOT}
export PYTHONPATH=${PYTESTAPPROOT}/proto:${PYTESTAPPROOT}/proto/gpuagent
python3 apps/<pytestapp> [arguments]
e.g: python3 apps/gpu_watch_client.py --node-ip 10.30.62.222 --id 31000000-0000-0000-0000-000000000000
```
