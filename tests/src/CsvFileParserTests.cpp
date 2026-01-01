#include <datalint/CsvFileParser.h>
#include <datalint/RawData.h>
#include <datalint/RawField.h>
#include <gtest/gtest.h>

#include <fstream>
#include <vector>

/// @brief Tests that the csv file parser can parse a simple CSV file.
TEST(CsvFileParserTest, CanInitializeWithFields) {
  // Create a temporary CSV file for testing
  const std::string tempCsvFile = "temp_test.csv";
  {
    std::ofstream outFile(tempCsvFile);
    outFile << "key1,value1\n";
    outFile << "key2,value2\n";
    outFile << "key1,value3\n";
  }
  datalint::input::CsvFileParser parser;
  const datalint::RawData rawData = parser.Parse(tempCsvFile);
  const auto& fields = rawData.Fields();
  ASSERT_EQ(fields.size(), 3);
  // Order of occurrence and key to value relationship should both be preserved
  EXPECT_EQ(fields[0].Key, "key1");
  EXPECT_EQ(fields[0].Value, "value1");
  EXPECT_EQ(fields[0].Location.Filename, tempCsvFile);
  EXPECT_EQ(fields[0].Location.Line, 1);
  EXPECT_EQ(fields[1].Key, "key2");
  EXPECT_EQ(fields[1].Value, "value2");
  EXPECT_EQ(fields[1].Location.Filename, tempCsvFile);
  EXPECT_EQ(fields[1].Location.Line, 2);
  EXPECT_EQ(fields[2].Key, "key1");
  EXPECT_EQ(fields[2].Value, "value3");
  EXPECT_EQ(fields[2].Location.Filename, tempCsvFile);
  EXPECT_EQ(fields[2].Location.Line, 3);

  int result = std::remove(tempCsvFile.c_str());
  ASSERT_EQ(result, 0);  // optional check that deletion succeeded
}
