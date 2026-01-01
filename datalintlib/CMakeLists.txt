add_library(datalintlib
    src/reader.cpp
    src/row.cpp
)

target_include_directories(datalintlib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(datalintlib PUBLIC cxx_std_20)

# Optional warnings (good for MSVC too)
if (MSVC)
    target_compile_options(datalintlib PRIVATE /W4)
else()
    target_compile_options(datalintlib PRIVATE -Wall -Wextra -Wpedantic)
endif()
