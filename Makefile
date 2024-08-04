# Makefile for Miles Hexapod Robot

# Variables
BOARD := milkv-duo
ARCH := riscv64
TOOLCHAIN := c906fdv-riscv64-unknown-linux-musl
IMAGE_TYPE := sd
BUILD_DIR := $(PWD)/build
OS_BUILD_DIR := $(BUILD_DIR)/os
SW_BUILD_DIR := $(BUILD_DIR)/sw
OS_DOCKER_IMAGE := milkvtech/milkv-duo:latest
SOFTWARE_DOCKER_IMAGE := miles-sw-build
BUILDROOT_CONTAINER_NAME := miles-milkv-duo-buildroot

# Targets
.PHONY: all os software clean

all: software os

# Build OS images
os:
	mkdir -p $(OS_BUILD_DIR)
	@echo "Building OS images for board $(BOARD)..."
	@if [ $$(docker ps -a -q -f name=$(BUILDROOT_CONTAINER_NAME)) ]; then \
	    docker rm -f $(BUILDROOT_CONTAINER_NAME); \
	fi
	@docker run -itd --name $(BUILDROOT_CONTAINER_NAME) -v $(PWD)/duo-buildroot-sdk:/home/work $(OS_DOCKER_IMAGE) /bin/bash
	@docker exec -it $(BUILDROOT_CONTAINER_NAME) /bin/bash -c "cd /home/work && cat /etc/issue && ./build.sh $(BOARD)-$(IMAGE_TYPE)"
	@echo "Copying Images"
	@rsync -av --ignore-existing $(PWD)/duo-buildroot-sdk/out $(OS_BUILD_DIR)
	@docker stop $(BUILDROOT_CONTAINER_NAME)

buildenv-container:
	@echo "Building buildenv container"
	@docker build -t $(SOFTWARE_DOCKER_IMAGE) -f ./Dockerfile .

# You need to manually go into the build folder and run ccmake due to issue with ncurses and docker
configure: buildenv-container
	@echo "Opening Configuration"
	@docker run -it $(SOFTWARE_DOCKER_IMAGE)
	
#Build the robot software
software: buildenv-container
	@mkdir -p $(SW_BUILD_DIR)
	@echo "Building Software..."
	@docker run -it -v $(SW_BUILD_DIR):/opt/miles/build/sw/ $(SOFTWARE_DOCKER_IMAGE) /usr/local/bin/build_project.sh $(ARCH) $(TOOLCHAIN) build

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."	
	@echo "Removing Docker Containers"
	@docker rm -f $(BUILDROOT_CONTAINER_NAME)
	@docker rm -f $(SOFTWARE_DOCKER_IMAGE)


