# EXPERIMENTAL cross toolchain: build an MSVC-ABI x86 Windows DLL on Linux using clang-cl + an
# xwin-splatted MSVC SDK. Unlike the llvm-mingw/libc++ build, the result uses MSVC's STL, so it is
# ABI-compatible with MSVC-built TygerFramework (which passes std::string by value across the
# plugin boundary).
#
# Prereqs:
#   - clang-cl on PATH
#   - lld-link on PATH at build time (e.g. export PATH=/opt/llvm-mingw/bin:$PATH)
#   - an xwin sysroot; default /opt/xwin-sdk, override with the XWIN_SDK env var or -DXWIN_SDK=<dir>

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

# The compiler check can't run a Windows exe on Linux; only compile/link in the probe.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(NOT DEFINED XWIN_SDK)
    if(DEFINED ENV{XWIN_SDK})
        set(XWIN_SDK "$ENV{XWIN_SDK}")
    else()
        set(XWIN_SDK "/opt/xwin-sdk")
    endif()
endif()

set(CMAKE_C_COMPILER clang-cl)
set(CMAKE_CXX_COMPILER clang-cl)
set(CMAKE_C_COMPILER_TARGET i686-pc-windows-msvc)
set(CMAKE_CXX_COMPILER_TARGET i686-pc-windows-msvc)
set(CMAKE_C_COMPILER_FRONTEND_VARIANT MSVC)
set(CMAKE_CXX_COMPILER_FRONTEND_VARIANT MSVC)

# System headers from the xwin sysroot (/imsvc keeps them out of -W/-WX diagnostics).
set(_xwin_inc "/imsvc ${XWIN_SDK}/crt/include /imsvc ${XWIN_SDK}/sdk/include/ucrt /imsvc ${XWIN_SDK}/sdk/include/um /imsvc ${XWIN_SDK}/sdk/include/shared")
set(CMAKE_C_FLAGS_INIT "${_xwin_inc}")
set(CMAKE_CXX_FLAGS_INIT "${_xwin_inc}")

# Match TygerFramework's runtime: release dynamic CRT (/MD). This is required for std::string
# ABI compatibility (the debug CRT changes _ITERATOR_DEBUG_LEVEL and the string layout), and the
# xwin sysroot only splats the release import libs by default.
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

# Library search from the xwin sysroot. CMake invokes lld-link directly (found on PATH), so no
# -fuse-ld is needed here.
set(_xwin_link "/libpath:${XWIN_SDK}/crt/lib/x86 /libpath:${XWIN_SDK}/sdk/lib/ucrt/x86 /libpath:${XWIN_SDK}/sdk/lib/um/x86")
set(CMAKE_EXE_LINKER_FLAGS_INIT "${_xwin_link}")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "${_xwin_link}")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "${_xwin_link}")

# Resolve against the xwin sysroot but NOT the Linux host programs. LIBRARY/INCLUDE/PACKAGE are
# BOTH (not ONLY) so that, when vcpkg chainloads this toolchain, ports can also find the vcpkg
# installed tree (added to CMAKE_PREFIX_PATH by vcpkg) in addition to the MSVC sysroot.
set(CMAKE_FIND_ROOT_PATH "${XWIN_SDK}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
