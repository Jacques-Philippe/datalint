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
    outFile << "key1,value1,Simple two-column row\n";
    outFile << "key2 , value2 , Leading and trailing spaces (unquoted) \n";
    outFile << "\"k,ey3\",\"val,ue3\",\"Embedded commas inside quoted fields\"\n";
    outFile << "\"key\"\"4\",\"value\"\"4\",\"Embedded double quotes (escaped by doubling)\"\n";
  }
  datalint::input::CsvFileParser parser;
  const datalint::RawData rawData = parser.Parse(tempCsvFile);
  const auto& fields = rawData.Fields();
  ASSERT_EQ(fields.size(), 4);
  // Order of occurrence and key to value relationship should both be preserved
  EXPECT_EQ(fields[0].Key, "key1");
  EXPECT_EQ(fields[0].Value, "value1,Simple two-column row");
  EXPECT_EQ(fields[0].Location.Filename, tempCsvFile);
  EXPECT_EQ(fields[0].Location.Line, 1);
  EXPECT_EQ(fields[1].Key, "key2");
  EXPECT_EQ(fields[1].Value, "value2,Leading and trailing spaces (unquoted)");
  EXPECT_EQ(fields[1].Location.Filename, tempCsvFile);
  EXPECT_EQ(fields[1].Location.Line, 2);
  EXPECT_EQ(fields[2].Key, "\"k,ey3\"");
  EXPECT_EQ(fields[2].Value, "\"val,ue3\",\"Embedded commas inside quoted fields\"");
  EXPECT_EQ(fields[2].Location.Filename, tempCsvFile);
  EXPECT_EQ(fields[2].Location.Line, 3);
  EXPECT_EQ(fields[3].Key, "\"key\"4\"");
  EXPECT_EQ(fields[3].Value, "\"value\"4\",\"Embedded double quotes (escaped by doubling)\"");
  EXPECT_EQ(fields[3].Location.Filename, tempCsvFile);
  EXPECT_EQ(fields[3].Location.Line, 4);

  int result = std::remove(tempCsvFile.c_str());
  ASSERT_EQ(result, 0);  // optional check that deletion of temporary file succeeded
}
