cmake_minimum_required(VERSION 3.21)

project("TygerMemory" LANGUAGES C CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompileOptions)
include(SimpleGitVersion)
include(MinHook)

# Build the DLL from every .cpp under TygerMemory/. dllmain.cpp (the DLL entry point) and
# pch.cpp are intentionally included: this is the TygerMemory DLL itself, not a vendored
# static lib (mtppp excludes them only because it vendors TygerMemory inside its own DLL).
file(GLOB TYGERMEMORY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/TygerMemory/*.cpp")

add_library(TygerMemory SHARED ${TYGERMEMORY_SOURCES})
add_library(tygermemory::tygermemory ALIAS TygerMemory)

target_include_directories(TygerMemory PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/TygerMemory")

target_link_libraries(TygerMemory PUBLIC minhook::minhook)

# Export decoration. The class headers gate __declspec(dllexport) on TYGERMEM_EXPORTS.
# Define TYGERMEM_EXPORTS / TYGERMEMORY_EXPORTS / _WINDOWS / _USRDLL consistently for the DLL build.
target_compile_definitions(TygerMemory PRIVATE
    TYGERMEM_EXPORTS
    TYGERMEMORY_EXPORTS
    _WINDOWS
    _USRDLL
)

# Cross-toolchain precompiled header: pch.h is force-included into every TU and left untouched.
target_precompile_headers(TygerMemory PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/TygerMemory/pch.h")

tygermemory_apply_compile_options(TygerMemory)
add_git_version_info(TygerMemory)

# Install the runtime DLL and import library flat into the install prefix.
install(TARGETS TygerMemory
    RUNTIME DESTINATION "."
    LIBRARY DESTINATION "."
    ARCHIVE DESTINATION "."
)

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    file(CREATE_LINK
        "${CMAKE_BINARY_DIR}/compile_commands.json"
        "${CMAKE_SOURCE_DIR}/compile_commands.json"
        SYMBOLIC
    )
endif()
