cmake_minimum_required(VERSION 3.10)
project(entt LANGUAGES CXX)

add_library(entt INTERFACE)

target_include_directories(entt INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
