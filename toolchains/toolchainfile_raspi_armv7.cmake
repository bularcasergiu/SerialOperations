include (CmakeForceCompiler)
message (STATUS "Generating for Raspian")
# set cmake internal stuff
set(CMAKE_SYSTEM_NAME RASPIAN)
set(CMAKE_SYSTEM_VERSION JESSIE)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# set actual compiler and linker paths
set(TOOLCHAIN_PREFIX "arm-linux-gnueabihf")
set(CMAKE_TOOLCHAIN_PREFIX "${TOOLCHAIN_PREFIX}-")
file(TO_CMAKE_PATH  $ENV{RASPI_SDK} RASPI_TOOLCHAIN_PATH)

set(CMAKE_C_COMPILER "${RASPI_TOOLCHAIN_PATH}/bin/${CMAKE_TOOLCHAIN_PREFIX}gcc.exe")
set(CMAKE_CXX_COMPILER "${RASPI_TOOLCHAIN_PATH}/bin/${CMAKE_TOOLCHAIN_PREFIX}g++.exe")
set(CMAKE_OBJCOPY "${RASPI_TOOLCHAIN_PATH}/bin/${CMAKE_TOOLCHAIN_PREFIX}objcopy.exe")
set(CMAKE_LINKER "${RASPI_TOOLCHAIN_PATH}/bin/${CMAKE_TOOLCHAIN_PREFIX}ld.exe")
