cmake_minimum_required(VERSION 3.10)
project(polar LANGUAGES CXX)

set(SDL_SHARED OFF)
set(SDL_STATIC ON)

add_subdirectory("external/entt")
add_subdirectory("external/glm")
add_subdirectory("external/SDL3")
add_subdirectory("external/glad")
add_subdirectory("external/stb_image")

file(GLOB_RECURSE POLAR_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_library(polar STATIC ${POLAR_SOURCES})

target_compile_features(polar PUBLIC cxx_std_17)

target_include_directories(polar PUBLIC "include")

target_link_libraries(polar
    PUBLIC
        glm
        SDL3-static
        glad
        stb_image
)
