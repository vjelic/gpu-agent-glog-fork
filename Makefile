CUR_DIR=$(PWD)

.PHONY: setup-ws
setup-ws:
	@cd $(CUR_DIR)/sw/nic/third-party/grpc
	@git submodule update --init --depth 1 --recursive -f
	@cd $(CUR_DIR)/sw/nic/third-party/protobuf
	@git submodule update --init --recursive -f
	@echo "updated module and workspace setup successful"


.PHONY: build-container
build-container:
	@docker build  . -f Dokerfile.rhel9 -t gpuagent-builder

.PHONY: gpuagent
gpuagent:
	@docker rm -f gpuagent-compiler || true
	@docker run --rm -it --privileged \
		--network host \
		-e "USER_NAME=$(shell whoami)" \
		-e "USER_UID=$(shell id -u)" \
		-e "USER_GID=$(shell id -g)" \
		--name gpuagent-compiler \
		-v $(PWD)/sw:/usr/src/github.com/ROCm/gpu-agent/sw \
		-w 	/usr/src/github.com/ROCm/gpu-agent/sw \
		gpuagent-builder

.PHONY: gpuagent-shell
gpuagent-shell:
	@docker run --rm -it --privileged \
		--network host \
		-e "USER_NAME=$(shell whoami)" \
		-e "USER_UID=$(shell id -u)" \
		-e "USER_GID=$(shell id -g)" \
		--name gpuagent-compiler \
		-v $(PWD)/sw:/usr/src/github.com/ROCm/gpu-agent/sw \
		-w 	/usr/src/github.com/ROCm/gpu-agent/sw \
		--entrypoint /bin/bash \
		gpuagent-builder
