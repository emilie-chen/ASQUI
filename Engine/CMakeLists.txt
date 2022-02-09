file(GLOB_RECURSE Engine_SourceFiles src/*.cpp src/*.h)

add_library(Engine ${Engine_SourceFiles})

target_include_directories(Engine
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Engine PRIVATE fmt::fmt fmt::fmt-header-only glm::glm)
