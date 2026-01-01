add_executable(datalinttool
    src/main.cpp
)

target_link_libraries(datalinttool
    PRIVATE datalintlib
)
