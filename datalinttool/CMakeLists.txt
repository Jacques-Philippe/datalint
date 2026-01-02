add_executable(datalinttool
    include/ExampleApplicationDescriptorResolver.h

    src/ExampleApplicationDescriptorResolver.cpp

    src/main.cpp
)

target_link_libraries(datalinttool
    PRIVATE datalintlib
)

target_include_directories(datalinttool
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
