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

# ── cglm ──────────────────────────────────────────────────────────────────────
FetchContent_Declare(
        cglm
        GIT_REPOSITORY https://github.com/recp/cglm.git
        GIT_TAG        v0.9.4
)

set(CGLM_SHARED  OFF CACHE BOOL "" FORCE)
set(CGLM_STATIC  ON  CACHE BOOL "" FORCE)
set(CGLM_USE_TEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(cglm)

# ── OpenGL ──────────────────────────────────────────────────────────────────────
find_package(OpenGL 3.3 REQUIRED)

# ── Executable ────────────────────────────────────────────────────────────────
add_executable(MGRS
        main.c
        main.h
        Window.c
        Window.h
        KeymapSettings.c
        KeymapSettings.h
        Global.c
        Global.h
        colors.h
        shaders.c
        shaders.h
)

target_link_libraries(MGRS PRIVATE
        glad
        glfw
        OpenGL::GL
        cglm
)

target_include_directories(MGRS PRIVATE ${cglm_SOURCE_DIR}/include)