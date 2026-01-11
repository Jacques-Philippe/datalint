include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) # Important for MSVC

FetchContent_MakeAvailable(googletest)

add_executable(datalintlib_tests
    src/RawDataTests.cpp
    src/CsvFileParserTests.cpp
    src/DefaultCsvApplicationDescriptorResolverTests.cpp

    src/Error/ErrorLogTests.cpp

    src/LayoutSpecification/ExpectedFieldTests.cpp
    src/LayoutSpecification/LayoutSpecificationTests.cpp
    src/LayoutSpecification/LayoutSpecificationBuilderTests.cpp
    src/LayoutSpecification/LayoutPatchTests.cpp
    src/LayoutSpecification/LayoutPatchOperationsTests.cpp

    src/Version/VersionTests.cpp
    src/Version/VersionRangeTests.cpp

    include/TestUtils.h
    include/datalint_test_namespace.h
)

target_link_libraries(datalintlib_tests
    PRIVATE
        datalintlib
        GTest::gtest_main
)

target_include_directories(datalintlib_tests
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

include(GoogleTest)
gtest_discover_tests(datalintlib_tests)
