### To generate source tarball the contains gpuagent and all its dependencies:

```
1. attach to docker/shell container
2. cd /sw/nic/
3. gpuagent/tools/scripts/build_pkg.sh -—gen-src-tarball --build
```

this generates source tree under `/tmp/build/src/github.com/pensando/sw/nic/`
and tar ball is generated at `/sw/gpuagent-src.tar.xz` and `--build` option
ensure that build is successful. If build is not successful, then source code
tarball generation is skipped.

Above steps can be used in sanities or in scripts that periodically push the
code to external repo


### To re-build source code (if any changes are made after generating source tree)

```
cd /tmp/build/src/github.com/pensando/sw/nic/gpuagent
make
```
