cmake_minimum_required(VERSION "3.10")

project(Xonix VERSION "1.0.0")

set(CMAKE_INCLUDE_CURRENT_DIR yes)

add_subdirectory(./external)
add_subdirectory(./src)
add_subdirectory(./docs)
