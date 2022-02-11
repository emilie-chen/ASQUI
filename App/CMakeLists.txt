file(GLOB_RECURSE App_SourceFiles src/*.cpp src/*.h)

add_executable(App ${App_SourceFiles})

target_include_directories(App
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(App Engine glm::glm fmt::fmt fmt::fmt-header-only)
