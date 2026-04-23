cmake_minimum_required(VERSION 3.20)
project(MGRS C)

set(CMAKE_C_STANDARD 11)

# ── Build type ────────────────────────────────────────────────────────────────
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# ── Vulkan ────────────────────────────────────────────────────────────────────
find_package(Vulkan REQUIRED)
find_program(GLSLC glslc HINTS $ENV{VULKAN_SDK}/bin)

# ── GLFW ──────────────────────────────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
)
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(glfw)

# ── Executable ────────────────────────────────────────────────────────────────
add_executable(MGRS
        main.c
        CoreVulkanUtilis.c
        CoreVulkanUtilis.h
        main.h
        global.h
        VulkanErrorMacro.h
)

target_link_libraries(MGRS PRIVATE
        Vulkan::Vulkan
        glfw
)