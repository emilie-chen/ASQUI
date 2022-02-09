file(GLOB_RECURSE App_SourceFiles src/*.cpp include/*.h)

add_executable(App ${App_SourceFiles})

target_include_directories(App
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(App Engine glm)
