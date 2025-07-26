# create container image for development environment with all necessary 
# compilation and development tools pre-installed.
all:
	echo "building dev container without insecure registry"
	docker build --build-arg USER=$(shell id -un) \
		--build-arg GROUP=$(shell id -gn) \
		--build-arg BUILD_BASE_IMAGE=$(BUILD_BASE_IMAGE) \
		--build-arg UID=$(shell id -u) \
		--build-arg GID=$(shell id -g) \
		-t ${GPUAGENT_BLD_CONTAINER_IMAGE} \
		. -f Dokerfile.rhel9
	echo "dev container build complete : ${GPUAGENT_BLD_CONTAINER_IMAGE}"
