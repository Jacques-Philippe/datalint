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
  auto selectedValues = selector.Select(parsedField);

  ASSERT_EQ(selectedValues.size(), 1u);
  ASSERT_NE(selectedValues[0], nullptr);
  EXPECT_EQ(selectedValues[0]->Value, "Value2");
  EXPECT_EQ(selectedValues[0]->Location.Filename, "file.txt");
  EXPECT_EQ(selectedValues[0]->Location.Line, 2);
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
  auto selectedValues = selector.Select(parsedField);

  ASSERT_EQ(selectedValues.size(), 0);
}
