#include <datalint/RuleSpecification/ValueAtIndexSelector.h>
#include <gtest/gtest.h>

/// @brief Tests that we can select a value at a given index from a ParsedField
TEST(ValueAtIndexSelectorTests, CanSelectValueAtIndex) {
  datalint::fieldparser::ParsedField parsedField;
  parsedField.Key = "TestKey";
  parsedField.Values = {
      {"Value1", {"file.txt", 1}},
      {"Value2", {"file.txt", 2}},
      {"Value3", {"file.txt", 3}},
  };
  datalint::rules::ValueAtIndexSelector selector(1);
  const datalint::fieldparser::RawValue& selectedValue = selector.Select(parsedField);
  EXPECT_EQ(selectedValue.Value, "Value2");
  EXPECT_EQ(selectedValue.Location.Filename, "file.txt");
  EXPECT_EQ(selectedValue.Location.Line, 2);
}

/// @brief Tests that selecting an out-of-range index throws an exception
TEST(ValueAtIndexSelectorTests, ThrowsWhenIndexOutOfRange) {
  datalint::fieldparser::ParsedField parsedField;
  parsedField.Key = "TestKey";
  parsedField.Values = {
      {"Value1", {"file.txt", 1}},
      {"Value2", {"file.txt", 2}},
  };
  datalint::rules::ValueAtIndexSelector selector(5);
  EXPECT_THROW(selector.Select(parsedField), std::out_of_range);

  datalint::rules::ValueAtIndexSelector selector2(-1);
  EXPECT_THROW(selector2.Select(parsedField), std::out_of_range);
}
