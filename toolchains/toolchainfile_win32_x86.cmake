message (STATUS "Generating for Windows")
# set cmake internal stuff
set(CMAKE_SYSTEM_NAME WINDOWS)
set(CMAKE_SYSTEM_VERSION 7)
set(CMAKE_SYSTEM_PROCESSOR X86)

# set actual compiler and linker paths
#set(TOOLCHAIN_PREFIX "arm-linux-gnueabihf")
#set(CMAKE_TOOLCHAIN_PREFIX "${TOOLCHAIN_PREFIX}-")
file(TO_CMAKE_PATH $ENV{CYGWIN_HOME} WIN_TOOLCHAIN_PATH)

set(CMAKE_C_COMPILER "${WIN_TOOLCHAIN_PATH}/bin/gcc.exe")
set(CMAKE_CXX_COMPILER "${WIN_TOOLCHAIN_PATH}/bin/g++.exe")
set(CMAKE_OBJCOPY "${WIN_TOOLCHAIN_PATH}/bin/objcopy.exe")
set(CMAKE_LINKER "${WIN_TOOLCHAIN_PATH}/bin/ld.exe")
