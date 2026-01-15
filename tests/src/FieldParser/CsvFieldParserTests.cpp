#include <datalint/FieldParser/CsvFieldParser.h>
#include <datalint/FieldParser/ParsedField.h>
#include <datalint/RawField.h>
#include <gtest/gtest.h>

/// @brief Test that we're able to parse a ParsedField from a RawField
TEST(CsvFieldParserTest, CanParseParsedFieldFromRawField) {
  datalint::fieldparser::CsvFieldParser parser;
  datalint::RawField rawField;
  rawField.Key = "TestKey";
  rawField.Value = "Value1,Value2,Value3";

  datalint::fieldparser::ParsedField parsedField = parser.ParseFieldValue(rawField);

  EXPECT_EQ(parsedField.Key, "TestKey");
  ASSERT_EQ(parsedField.Values.size(), 3);
  EXPECT_EQ(parsedField.Values[0].Value, "Value1");
  EXPECT_EQ(parsedField.Values[1].Value, "Value2");
  EXPECT_EQ(parsedField.Values[2].Value, "Value3");
}
