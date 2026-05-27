# Applies project-wide compile options to a TygerMemory target.
# Distinguishes MSVC-style frontends (cl.exe / clang-cl) from GCC-style (clang on MinGW).
# Deliberately NO -Werror / /WX: the existing sources carry warnings that are not treated
# as errors.
function(tygermemory_apply_compile_options target)
    target_compile_features(${target} PRIVATE cxx_std_17)

    if(MSVC OR CMAKE_CXX_COMPILER_FRONTEND_VARIANT STREQUAL "MSVC")
        target_compile_options(${target} PRIVATE /W3 /utf-8)
        target_compile_definitions(${target} PRIVATE
            WIN32_LEAN_AND_MEAN
            NOMINMAX
            _CRT_SECURE_NO_WARNINGS
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall
            -Wno-unknown-pragmas
        )
        target_compile_definitions(${target} PRIVATE
            WIN32_LEAN_AND_MEAN
            NOMINMAX
        )
    endif()
endfunction()
