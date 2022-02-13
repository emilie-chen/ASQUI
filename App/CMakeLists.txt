file(GLOB_RECURSE App_SourceFiles src/*.cpp src/*.h src/*.m src/*.mm)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MONO_PATH "${CMAKE_CURRENT_LIST_DIR}/../vendor/mono/osx")
    set(MONO_INCLUDE ${MONO_PATH}/include/mono-2.0)
    set(MONO_LIB ${MONO_PATH}/lib/libmonosgen-2.0.a)
else()
    set(MONO_INCLUDE "/usr/include/mono-2.0")
    set(MONO_LIB "/usr/lib/libmono2.0.so")
endif()

add_executable(App ${App_SourceFiles})

target_include_directories(App
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        ${MONO_INCLUDE}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(App Engine glm::glm fmt::fmt fmt::fmt-header-only spdlog::spdlog ${MONO_LIB})
