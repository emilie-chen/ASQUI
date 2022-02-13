file(GLOB_RECURSE Engine_SourceFiles src/*.cpp src/*.h src/*.m src/*.mm)

add_library(Engine ${Engine_SourceFiles})

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MONO_PATH "${CMAKE_CURRENT_LIST_DIR}/../vendor/mono/osx")
    set(MONO_INCLUDE ${MONO_PATH}/include/mono-2.0)
    set(MONO_LIB ${MONO_PATH}/lib/libmonosgen-2.0.a)
else()
    set(MONO_INCLUDE "/usr/include/mono-2.0")
    set(MONO_LIB "/usr/lib/libmono2.0.so")
endif()

target_include_directories(Engine
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        ${MONO_INCLUDE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Engine PRIVATE fmt::fmt fmt::fmt-header-only glm::glm spdlog::spdlog ${MONO_LIB})
