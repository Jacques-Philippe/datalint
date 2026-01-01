include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Important for MSVC

FetchContent_MakeAvailable(googletest)

add_executable(datalintlib_tests
    src/reader_tests.cpp
    src/RawDataTests.cpp
)

target_link_libraries(datalintlib_tests
    PRIVATE
        datalintlib
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(datalintlib_tests)
