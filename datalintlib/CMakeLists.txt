add_library(datalintlib

    include/datalint/ApplicationDescriptor/ApplicationDescriptor.h
    include/datalint/ApplicationDescriptor/IApplicationDescriptorResolver.h
    include/datalint/ApplicationDescriptor/ResolveResult.h
    include/datalint/ApplicationDescriptor/ResolveError.h
    include/datalint/ApplicationDescriptor/DefaultCsvApplicationDescriptorResolver.h

    include/datalint/Error/ErrorLog.h
    include/datalint/Error/ErrorCollector.h
    include/datalint/Error/datalint_error_namespace.h

    include/datalint/FieldParser/RawValue.h
    include/datalint/FieldParser/ParsedField.h
    include/datalint/FieldParser/IFieldParser.h
    include/datalint/FieldParser/CsvFieldParser.h
    include/datalint/FieldParser/ParsedData.h
    include/datalint/FieldParser/ParsedDataBuilder.h

    include/datalint/FileParser/IFileParser.h
    include/datalint/FileParser/CsvFileParser.h
    include/datalint/FileParser/datalint_input_namespace.h

    include/datalint/LayoutSpecification/ExpectedField.h
    include/datalint/LayoutSpecification/FieldOrderingConstraint.h
    include/datalint/LayoutSpecification/UnexpectedFieldStrictness.h
    include/datalint/LayoutSpecification/LayoutSpecification.h
    include/datalint/LayoutSpecification/LayoutSpecificationBuilder.h
    include/datalint/LayoutSpecification/LayoutPatch.h
    include/datalint/LayoutSpecification/LayoutSpecificationValidator.h
    include/datalint/LayoutSpecification/LayoutPatchOperations.h

    include/datalint/RuleSpecification/RuleContext.h
    include/datalint/RuleSpecification/IValueSelector.h
    include/datalint/RuleSpecification/ValueAtIndexSelector.h
    include/datalint/RuleSpecification/AllValuesSelector.h
    include/datalint/RuleSpecification/IValueRule.h
    include/datalint/RuleSpecification/IntegerInRangeRule.h
    include/datalint/RuleSpecification/IRulePatchOperation.h
    include/datalint/RuleSpecification/AddFieldRulePatchOperation.h
    include/datalint/RuleSpecification/RemoveFieldRulePatchOperation.h
    include/datalint/RuleSpecification/RulePatch.h
    include/datalint/RuleSpecification/RuleSpecification.h
    include/datalint/RuleSpecification/RuleValidator.h
    include/datalint/RuleSpecification/RuleSpecificationBuilder.h

    include/datalint/RawData.h
    include/datalint/RawField.h
    include/datalint/SourceLocation.h
    include/datalint/StringUtils.h

    include/datalint/Version/Version.h
    include/datalint/Version/VersionRange.h

    include/datalint/datalint_namespace.h

    src/ApplicationDescriptor/DefaultCsvApplicationDescriptorResolver.cpp

    src/FieldParser/CsvFieldParser.cpp
    src/FieldParser/ParsedDataBuilder.cpp

    src/FileParser/CsvFileParser.cpp

    src/LayoutSpecification/LayoutSpecification.cpp
    src/LayoutSpecification/LayoutSpecificationBuilder.cpp
    src/LayoutSpecification/LayoutSpecificationValidator.cpp

    src/RuleSpecification/RuleValidator.cpp

    src/RawData.cpp
    src/StringUtils.cpp
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

install(TARGETS datalintlib
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)
install(DIRECTORY include/datalint
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
        PATTERN "gtest" EXCLUDE
        PATTERN "gmock" EXCLUDE
)
