CUR_DIR = $(PWD)
CUR_USER:=$(shell whoami)
CUR_TIME:=$(shell date +%Y-%m-%d_%H.%M.%S)
GPUAGENT_BLD_CONTAINER_IMAGE ?= gpuagent-builder
CONTAINER_NAME := gpuagent-ctr-${CUR_USER}_${CUR_TIME}

.PHONY: build-container
build-container:
	@docker build  . -f Dokerfile.rhel9 \
		-t ${GPUAGENT_BLD_CONTAINER_IMAGE}

.PHONY: gpuagent
gpuagent:
	@docker run --rm -it --privileged \
		--network host \
		-e "USER_NAME=$(shell whoami)" \
		-e "USER_UID=$(shell id -u)" \
		-e "USER_GID=$(shell id -g)" \
		--name ${CONTAINER_NAME} \
		-v $(PWD)/sw:/usr/src/github.com/ROCm/gpu-agent/sw \
		-w 	/usr/src/github.com/ROCm/gpu-agent/sw \
		${GPUAGENT_BLD_CONTAINER_IMAGE}

