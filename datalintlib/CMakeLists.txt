add_library(datalintlib
    include/datalint/FileParser/IFileParser.h
    include/datalint/FileParser/CsvFileParser.h
    include/datalint/FileParser/datalint_input_namespace.h
    include/datalint/ApplicationDescriptor/ApplicationDescriptor.h
    include/datalint/ApplicationDescriptor/IApplicationDescriptorResolver.h
    include/datalint/RawData.h
    include/datalint/RawField.h
    include/datalint/SourceLocation.h
    include/datalint/datalint_namespace.h

    src/FileParser/CsvFileParser.cpp
    src/RawData.cpp
)

target_include_directories(datalintlib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/external/csv2/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(datalintlib PUBLIC cxx_std_20)

# Optional warnings (good for MSVC too)
if (MSVC)
    target_compile_options(datalintlib PRIVATE /W4)
else()
    target_compile_options(datalintlib PRIVATE -Wall -Wextra -Wpedantic)
endif()
