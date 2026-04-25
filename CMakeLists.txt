cmake_minimum_required(VERSION 3.20)
project(MGRS C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# ── GLAD ────────────────────────────────────────────────────────────────────
add_library(glad STATIC
    glad/glad.c
)
target_include_directories(glad PUBLIC glad)

# ── GLFW ──────────────────────────────────────────────────────────────────────
include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        3.4
)

# Disable GLFW extras we don't need
set(GLFW_BUILD_DOCS     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS    OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)


# ── OpenGL ──────────────────────────────────────────────────────────────────────
find_package(OpenGL 3.3 REQUIRED)

# ── Executable ────────────────────────────────────────────────────────────────
add_executable(MGRS
        main.c
        main.h
        Window.c
        Window.h
)

target_link_libraries(MGRS PRIVATE
        glad
        glfw
        OpenGL::GL
)