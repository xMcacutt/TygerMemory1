# CMake toolchain file for cross-compiling Win32 x86 binaries from Linux using LLVM-MinGW.
# Expects LLVM-MinGW unpacked at /opt/llvm-mingw (override via LLVM_MINGW_ROOT).

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR i686)

if(NOT DEFINED LLVM_MINGW_ROOT)
    set(LLVM_MINGW_ROOT "/opt/llvm-mingw")
endif()

set(TRIPLE_PREFIX "i686-w64-mingw32")

set(CMAKE_C_COMPILER "${LLVM_MINGW_ROOT}/bin/${TRIPLE_PREFIX}-clang")
set(CMAKE_CXX_COMPILER "${LLVM_MINGW_ROOT}/bin/${TRIPLE_PREFIX}-clang++")
set(CMAKE_RC_COMPILER "${LLVM_MINGW_ROOT}/bin/${TRIPLE_PREFIX}-windres")
set(CMAKE_AR "${LLVM_MINGW_ROOT}/bin/${TRIPLE_PREFIX}-ar" CACHE FILEPATH "")
set(CMAKE_RANLIB "${LLVM_MINGW_ROOT}/bin/${TRIPLE_PREFIX}-ranlib" CACHE FILEPATH "")

set(CMAKE_FIND_ROOT_PATH "${LLVM_MINGW_ROOT}/${TRIPLE_PREFIX}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# LIBRARY/INCLUDE/PACKAGE are BOTH (not ONLY) so CMake searches the vcpkg installed
# tree (added to CMAKE_PREFIX_PATH by vcpkg.cmake) in addition to the MinGW sysroot.
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)

# Statically link the C/C++ runtimes into the plugin DLL.
set(CMAKE_C_FLAGS_INIT "-m32")
set(CMAKE_CXX_FLAGS_INIT "-m32 -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-m32 -static -static-libgcc")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "-m32 -static -static-libgcc")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "-m32 -static -static-libgcc")
