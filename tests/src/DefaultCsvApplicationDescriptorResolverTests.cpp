#include <TestUtils.h>
#include <datalint/ApplicationDescriptor/DefaultCsvApplicationDescriptorResolver.h>
#include <datalint/ApplicationDescriptor/ResolveError.h>
#include <datalint/ApplicationDescriptor/ResolveResult.h>
#include <datalint/FileParser/CsvFileParser.h>
#include <datalint/RawData.h>
#include <datalint/RawField.h>
#include <datalint/Version/Version.h>
#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <vector>

/// @brief Tests that an error is received for the application name missing from the raw data.
TEST(DefaultCsvApplicationDescriptorResolverTest, ReturnsErrorWhenApplicationNameMissing) {
  // Create a temporary CSV file for testing
  const std::string tempCsvFile =
      datalint::test::MakeTempCsvFilename("ReturnsErrorWhenApplicationNameMissing");
  {
    std::ofstream outFile(tempCsvFile);
    outFile << "key1,value1,Simple two-column row\n";
    outFile << "key2 , value2 , Leading and trailing spaces (unquoted) \n";
    outFile << "\"k,ey3\",\"val,ue3\",\"Embedded commas inside quoted fields\"\n";
    outFile << "\"key\"\"4\",\"value\"\"4\",\"Embedded double quotes (escaped by doubling)\"\n";
  }
  datalint::input::CsvFileParser parser;
  const datalint::RawData rawData = parser.Parse(tempCsvFile);
  auto resolver = datalint::DefaultCsvApplicationDescriptorResolver();
  const auto result = resolver.Resolve(rawData);

  ASSERT_FALSE(result.Success());
  ASSERT_EQ(result.Errors.size(), 1);
  EXPECT_EQ(result.Errors[0].Code, datalint::ResolveErrorCode::MissingRequiredField);
  EXPECT_EQ(result.Errors[0].Field, "ApplicationName");

  int removeResult = std::remove(tempCsvFile.c_str());
  ASSERT_EQ(removeResult, 0);  // optional check that deletion of temporary file succeeded
}

/// @brief Tests that an error is received for the application version missing from the raw data.
TEST(DefaultCsvApplicationDescriptorResolverTest, ReturnsErrorWhenApplicationVersionMissing) {
  // Create a temporary CSV file for testing
  const std::string tempCsvFile =
      datalint::test::MakeTempCsvFilename("ReturnsErrorWhenApplicationVersionMissing");
  {
    std::ofstream outFile(tempCsvFile);
    outFile << "key1,value1,Simple two-column row\n";
    outFile << "ApplicationName,Example Application,The name of the application\n";
    outFile << "\"k,ey3\",\"val,ue3\",\"Embedded commas inside quoted fields\"\n";
    outFile << "\"key\"\"4\",\"value\"\"4\",\"Embedded double quotes (escaped by doubling)\"\n";
  }
  datalint::input::CsvFileParser parser;
  const datalint::RawData rawData = parser.Parse(tempCsvFile);
  auto resolver = datalint::DefaultCsvApplicationDescriptorResolver();
  const auto result = resolver.Resolve(rawData);

  ASSERT_FALSE(result.Success());
  ASSERT_EQ(result.Errors.size(), 1);
  EXPECT_EQ(result.Errors[0].Code, datalint::ResolveErrorCode::MissingRequiredField);
  EXPECT_EQ(result.Errors[0].Field, "ApplicationVersion");

  int removeResult = std::remove(tempCsvFile.c_str());
  ASSERT_EQ(removeResult, 0);  // optional check that deletion of temporary file succeeded
}

/// @brief Tests that an error is received for duplicate application name fields in the raw data.
TEST(DefaultCsvApplicationDescriptorResolverTest, ReturnsErrorWhenDuplicateApplicationName) {
  // Create a temporary CSV file for testing
  const std::string tempCsvFile =
      datalint::test::MakeTempCsvFilename("ReturnsErrorWhenDuplicateApplicationName");
  {
    std::ofstream outFile(tempCsvFile);
    outFile << "ApplicationName,Example Application,The name of the application\n";
    outFile << "\"k,ey3\",\"val,ue3\",\"Embedded commas inside quoted fields\"\n";
    outFile << "ApplicationVersion,1.0.0,The version of the application\n";
    outFile << "ApplicationName,Another Application,Duplicate application name\n";
  }
  datalint::input::CsvFileParser parser;
  const datalint::RawData rawData = parser.Parse(tempCsvFile);
  auto resolver = datalint::DefaultCsvApplicationDescriptorResolver();
  const auto result = resolver.Resolve(rawData);

  ASSERT_FALSE(result.Success());
  ASSERT_EQ(result.Errors.size(), 1);
  EXPECT_EQ(result.Errors[0].Code, datalint::ResolveErrorCode::DuplicateField);
  EXPECT_EQ(result.Errors[0].Field, "ApplicationName");

  int removeResult = std::remove(tempCsvFile.c_str());
  ASSERT_EQ(removeResult, 0);  // optional check that deletion of temporary file succeeded
}
/// @brief Tests that an error is received for duplicate application version fields in the raw data.
TEST(DefaultCsvApplicationDescriptorResolverTest, ReturnsErrorWhenDuplicateApplicationVersion) {
  // Create a temporary CSV file for testing
  const std::string tempCsvFile =
      datalint::test::MakeTempCsvFilename("ReturnsErrorWhenDuplicateApplicationVersion");
  {
    std::ofstream outFile(tempCsvFile);
    outFile << "ApplicationName,Example Application,The name of the application\n";
    outFile << "ApplicationVersion,1.0.0,The version of the application\n";
    outFile << "\"k,ey3\",\"val,ue3\",\"Embedded commas inside quoted fields\"\n";
    outFile << "ApplicationVersion,2.0.0,Duplicate application version\n";
  }
  datalint::input::CsvFileParser parser;
  const datalint::RawData rawData = parser.Parse(tempCsvFile);
  auto resolver = datalint::DefaultCsvApplicationDescriptorResolver();
  const auto result = resolver.Resolve(rawData);

  ASSERT_FALSE(result.Success());
  ASSERT_EQ(result.Errors.size(), 1);
  EXPECT_EQ(result.Errors[0].Code, datalint::ResolveErrorCode::DuplicateField);
  EXPECT_EQ(result.Errors[0].Field, "ApplicationVersion");

  int removeResult = std::remove(tempCsvFile.c_str());
  ASSERT_EQ(removeResult, 0);  // optional check that deletion of temporary file succeeded
}

/// @brief Tests that a valid application descriptor is returned when both name and version are
/// present and unique.
TEST(DefaultCsvApplicationDescriptorResolverTest, ReturnsValidDescriptorWhenDataIsValid) {
  // Create a temporary CSV file for testing
  const std::string tempCsvFile =
      datalint::test::MakeTempCsvFilename("ReturnsValidDescriptorWhenDataIsValid");
  {
    std::ofstream outFile(tempCsvFile);
    outFile << "ApplicationName,Example Application,The name of the application\n";
    outFile << "ApplicationVersion,1.0.0,The version of the application\n";
    outFile << "\"k,ey3\",\"val,ue3\",\"Embedded commas inside quoted fields\"\n";
    outFile << "\"key\"\"4\",\"value\"\"4\",\"Embedded double quotes (escaped by doubling)\"\n";
  }
  datalint::input::CsvFileParser parser;
  const datalint::RawData rawData = parser.Parse(tempCsvFile);
  auto resolver = datalint::DefaultCsvApplicationDescriptorResolver();
  const auto result = resolver.Resolve(rawData);

  const auto expectedVersion = datalint::Version::Parse("1.0.0");
  ASSERT_TRUE(result.Success());
  ASSERT_TRUE(result.Descriptor.has_value());
  EXPECT_EQ(result.Descriptor->Name(), "Example Application");
  EXPECT_EQ(result.Descriptor->Version(), expectedVersion);
  int removeResult = std::remove(tempCsvFile.c_str());
  ASSERT_EQ(removeResult, 0);  // optional check that deletion of temporary file succeeded
}
