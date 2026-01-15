#include <datalint/FieldParser/CsvFieldParser.h>
#include <datalint/FieldParser/ParsedDataBuilder.h>
#include <datalint/FieldParser/ParsedField.h>
#include <datalint/RawField.h>
#include <gtest/gtest.h>

/// @brief Test that we're able to build a ParsedData from RawData
TEST(ParserDataBuilderTest, CanBuildParsedDataFromRawData) {
  datalint::RawField rawField;
  rawField.Key = "TestKey";
  rawField.Value = "Value1,Value2,Value3";

  datalint::RawData rawData({rawField});

  datalint::fieldparser::ParsedDataBuilder builder(
      std::make_unique<datalint::fieldparser::CsvFieldParser>());

  datalint::fieldparser::ParsedData parsedData = builder.Build(rawData);

  const auto& fields = parsedData.Fields();
  ASSERT_EQ(fields.size(), 1);
  const datalint::fieldparser::ParsedField& parsedField = fields[0];
  EXPECT_EQ(parsedField.Key, "TestKey");
  ASSERT_EQ(parsedField.Values.size(), 3);
  EXPECT_EQ(parsedField.Values[0].Value, "Value1");
  EXPECT_EQ(parsedField.Values[1].Value, "Value2");
  EXPECT_EQ(parsedField.Values[2].Value, "Value3");
}
