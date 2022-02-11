cmake_minimum_required(VERSION 3.19)

project(ASQUI)

set(CMAKE_CXX_STANDARD 20)

# vcpkg dependencies
find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_subdirectory(Engine)
add_subdirectory(App)