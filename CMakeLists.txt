cmake_minimum_required(VERSION 3.20)

project(datalint_tool
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(datalintlib)
add_subdirectory(datalinttool)
add_subdirectory(tests)
