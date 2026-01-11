add_library(datalintlib
    include/datalint/FileParser/IFileParser.h
    include/datalint/FileParser/CsvFileParser.h
    include/datalint/FileParser/datalint_input_namespace.h
    include/datalint/ApplicationDescriptor/ApplicationDescriptor.h
    include/datalint/ApplicationDescriptor/IApplicationDescriptorResolver.h
    include/datalint/ApplicationDescriptor/ResolveResult.h
    include/datalint/ApplicationDescriptor/ResolveError.h
    include/datalint/ApplicationDescriptor/DefaultCsvApplicationDescriptorResolver.h
    include/datalint/Error/ErrorLog.h
    include/datalint/Error/ErrorCollector.h
    include/datalint/Error/datalint_error_namespace.h
    include/datalint/LayoutSpecification/ExpectedField.h
    include/datalint/LayoutSpecification/LayoutSpecification.h
    include/datalint/LayoutSpecification/LayoutSpecificationBuilder.h
    include/datalint/LayoutSpecification/LayoutPatch.h
    include/datalint/LayoutSpecification/LayoutPatchOperations.h
    include/datalint/Version/Version.h
    include/datalint/Version/VersionRange.h
    include/datalint/RawData.h
    include/datalint/RawField.h
    include/datalint/SourceLocation.h
    include/datalint/datalint_namespace.h

    src/FileParser/CsvFileParser.cpp
    src/ApplicationDescriptor/DefaultCsvApplicationDescriptorResolver.cpp
    src/LayoutSpecification/LayoutSpecification.cpp
    src/LayoutSpecification/LayoutSpecificationBuilder.cpp
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
