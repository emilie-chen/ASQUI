cmake_minimum_required(VERSION 3.19)

project(ASQUI)

set(CMAKE_CXX_STANDARD 20)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
enable_language(OBJC)
enable_language(OBJCXX)
endif()

# vcpkg dependencies
find_package(fmt CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MONO_PATH "${CMAKE_CURRENT_LIST_DIR}/../vendor/mono/osx")
else()
    include(FindMono.cmake)
endif()

#find_package(Iconv CONFIG REQUIRED)

add_subdirectory(Engine)
add_subdirectory(App)