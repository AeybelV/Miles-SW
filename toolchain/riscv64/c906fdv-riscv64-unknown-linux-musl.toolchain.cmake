add_compile_definitions(BOARD="milkv_duo")

# Define the C compiler and C++ compiler for RISC-V
SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_SYSTEM_PROCESSOR riscv64)

set(TOOLCHAIN_PREFIX riscv64-unknown-linux-musl)

# Specify the cross compiler
SET(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)

# Specify the target environment
SET(CMAKE_FIND_ROOT_PATH /opt/riscv/${TOOLCHAIN_PREFIX})

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)


SET(CMAKE_C_FLAGS "-mcpu=c906fdv -march=rv64imafdcv0p7xthead -mcmodel=medany -mabi=lp64d")
SET(CMAKE_CXX_FLAGS "-mcpu=c906fdv -march=rv64imafdcv0p7xthead -mcmodel=medany -mabi=lp64d")

SET(CMAKE_EXE_LINKER_FLAGS "-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64")

# adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search headers and libraries in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
